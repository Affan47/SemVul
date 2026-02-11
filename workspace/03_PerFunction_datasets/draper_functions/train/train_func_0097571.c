xmms_statfs_is_remote (const gchar *path)
{
	struct statfs st;

	if (statfs (path, &st) == -1) {
		xmms_log_error ("Failed to run statfs, will not guess.");
		return FALSE;
	}

	if (st.f_type == 0xFF534D42 ||
	    st.f_type == 0x6969 ||
	    st.f_type == 0x517B) {
		return TRUE;
	}

	return FALSE;
}
