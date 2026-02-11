go_shell_arg_to_uri (char const *arg)
{
	GFile *file;
	gchar *tmp;
	int fd;


	if (is_fd_uri (arg, &fd))
		return g_strdup (arg);

	file = g_file_new_for_commandline_arg (arg);
	tmp = g_file_get_uri (file);
	g_object_unref (file);
	return tmp;
}
