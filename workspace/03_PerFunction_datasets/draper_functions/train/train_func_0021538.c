get_rc_dir(void)
{

	if (!claws_rc_dir) {
		claws_rc_dir = g_strconcat(get_home_dir(), G_DIR_SEPARATOR_S,
				     RC_DIR, NULL);
		debug_print("using default rc_dir %s\n", claws_rc_dir);
	}
	return claws_rc_dir;
}
