gsf_output_stdio_close (GsfOutput *output)
{
	GsfOutputStdio *stdio = GSF_OUTPUT_STDIO (output);
	gboolean res;
	char *backup_filename = NULL;
	GDateTime *modtime;

	if (stdio->file == NULL)
		return FALSE;

	if (gsf_output_error (output)) {
		res = TRUE;
		if (!stdio->keep_open && !close_file_helper (stdio, FALSE))
			res = FALSE;

		if (!unlink_file_helper (stdio))
			res = FALSE;

		return res;
	}

	if (stdio->keep_open) {
		gboolean res = (0 == fflush (stdio->file));
		if (!res)
			gsf_output_set_error (output, errno,
					      "Failed to flush.");
		stdio->file = NULL;
		return res;
	}

	res = close_file_helper (stdio, TRUE);


	if (!stdio->real_filename)
		return res;
	if (!res) {
		unlink_file_helper (stdio);
		return FALSE;
	}


	if (stdio->create_backup_copy) {
		gint result;
		backup_filename = g_strconcat (stdio->real_filename, ".bak", NULL);
		result = rename_wrapper (stdio->real_filename, backup_filename);
		if (result != 0) {
			char *utf8name = g_filename_display_name (backup_filename);
			gsf_output_set_error (output, errno,
					      "Could not backup the original as %s.",
					      utf8name);
			g_free (utf8name);
			g_unlink (stdio->temp_filename);
			res = FALSE;
			goto out;
		}
	}


	if (rename_wrapper (stdio->temp_filename, stdio->real_filename) != 0) {
		gint saved_errno = errno;
		if (backup_filename != NULL &&
		    rename_wrapper (backup_filename, stdio->real_filename) != 0)
			saved_errno = errno;
		res = gsf_output_set_error (output,
					    saved_errno,
					    "%s", g_strerror (saved_errno));
		goto out;
	}

	modtime = gsf_output_get_modtime (output);
	if (modtime) {
#ifdef UTIME_AVAILABLE
		struct utimbuf ut;

		ut.actime = time (NULL);
		ut.modtime = g_date_time_to_unix (modtime);


		(void)utime (stdio->real_filename, &ut);
#endif
	}


	g_chmod (stdio->real_filename, stdio->st.st_mode);
#ifdef HAVE_CHOWN
	if (chown_wrapper (stdio->real_filename,
			   stdio->st.st_uid,
			   stdio->st.st_gid)) {

		chown_wrapper (stdio->real_filename, -1, stdio->st.st_gid);
		chown_wrapper (stdio->real_filename, stdio->st.st_uid, -1);
	}
	g_chmod (stdio->real_filename, stdio->st.st_mode);
#endif

out:
	g_free (backup_filename);

	return res;
}
