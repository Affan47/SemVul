check_socket_permissions(void)
{
	struct stat socket_stat;

	if (g_lstat(socket_info.file_name, &socket_stat) == 0)
	{

		if (socket_stat.st_uid != getuid())
		{
			const gchar *msg = _(

	"Geany tried to access the Unix Domain socket of another instance running as another user.\n"
	"This is a fatal error and Geany will now quit.");
			g_warning("%s", msg);
			dialogs_show_msgbox(GTK_MESSAGE_ERROR, "%s", msg);
			exit(1);
		}
	}
}
