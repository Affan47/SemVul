_gck_debug_flag_is_set (GckDebugFlags flag)
{
	if G_UNLIKELY (!initialized_flags)
		initialize_debug_flags ();
	return (flag & current_flags) != 0;
}
