gitg_shell_new_synchronized (guint buffer_size)
{
	g_assert (buffer_size > 0);

	return GITG_SHELL (g_object_new (GITG_TYPE_SHELL,
	                                  "buffer_size",
	                                  buffer_size,
	                                  "synchronized",
	                                  TRUE,
	                                  NULL));
}
