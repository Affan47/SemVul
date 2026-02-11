copy_file (char *dl_src, char *dl_dest, int permissions)
{
	int tmp_src, tmp_dest;
	gboolean ok = FALSE;
	char dl_tmp[4096];
	int return_tmp, return_tmp2;

	if ((tmp_src = g_open (dl_src, O_RDONLY | OFLAGS, 0600)) == -1)
	{
		g_fprintf (stderr, "Unable to open() file '%s' (%s) !", dl_src,
				  strerror (errno));
		return FALSE;
	}

	if ((tmp_dest =
		 g_open (dl_dest, O_WRONLY | O_CREAT | O_TRUNC | OFLAGS, permissions)) < 0)
	{
		close (tmp_src);
		g_fprintf (stderr, "Unable to create file '%s' (%s) !", dl_src,
				  strerror (errno));
		return FALSE;
	}

	for (;;)
	{
		return_tmp = read (tmp_src, dl_tmp, sizeof (dl_tmp));

		if (!return_tmp)
		{
			ok = TRUE;
			break;
		}

		if (return_tmp < 0)
		{
			fprintf (stderr, "download_move_to_completed_dir(): "
				"error reading while moving file to save directory (%s)",
				 strerror (errno));
			break;
		}

		return_tmp2 = write (tmp_dest, dl_tmp, return_tmp);

		if (return_tmp2 < 0)
		{
			fprintf (stderr, "download_move_to_completed_dir(): "
				"error writing while moving file to save directory (%s)",
				 strerror (errno));
			break;
		}

		if (return_tmp < sizeof (dl_tmp))
		{
			ok = TRUE;
			break;
		}
	}

	close (tmp_dest);
	close (tmp_src);
	return ok;
}
