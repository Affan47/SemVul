remove_socket_link_full(void)
{
	gchar real_path[512];
	gsize len;

	real_path[0] = '\0';


	len = readlink(socket_info.file_name, real_path, sizeof(real_path) - 1);
	if ((gint) len > 0)
	{
		real_path[len] = '\0';
		g_unlink(real_path);
	}
	g_unlink(socket_info.file_name);
}
