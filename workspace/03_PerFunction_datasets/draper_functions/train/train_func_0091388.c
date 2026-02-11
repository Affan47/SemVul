connect_to_server
	(
	)
	{
	if (!static_path)
		return false;
#ifndef WIN32
	if (server_socket >= 0)
		{
		close(server_socket);
		gdk_input_remove(server_input_tag);
		}
	server_socket = server_input_tag = -1;
	struct sockaddr_un addr;
	addr.sun_family = AF_UNIX;

	char *home = getenv("HOME");
	addr.sun_path[0] = 0;
	if (home)
		{
		strcpy(addr.sun_path, home);
		strcat(addr.sun_path, "/.exult/exultserver");
		if (!U7exists(addr.sun_path))
			addr.sun_path[0] = 0;
		}
	if (!addr.sun_path[0])
		{
	        strcpy(addr.sun_path, static_path);
        	char *pstatic = strrchr(addr.sun_path, '/');
	        if (pstatic && !pstatic[1])
        	        {
                	pstatic[0] = 0;
	                pstatic = strrchr(addr.sun_path, '/');
        	        }
	        if (!pstatic)
        	        {
                	cout << "Can't find gamedat for socket" << endl;
	                return false;
        	        }
	        strcpy(pstatic + 1, "gamedat/exultserver");
		}
	server_socket = socket(PF_LOCAL, SOCK_STREAM, 0);
	if (server_socket < 0)
		{
		perror("Failed to open map-editor socket");
		return false;
		}


	cout << "Trying to connect to server at '" << addr.sun_path << "'"
							<< endl;
	if (connect(server_socket, (struct sockaddr *) &addr,
		      sizeof(addr.sun_family) + strlen(addr.sun_path)) == -1)
		{
		perror("Socket connect");
		close(server_socket);
		server_socket = -1;
		return false;
		}
	server_input_tag = gdk_input_add(server_socket,
			GDK_INPUT_READ, Read_from_server, this);
#else

	if (server_socket != -1) Exult_server::disconnect_from_server();
	if (server_input_tag != -1) gtk_timeout_remove(server_input_tag);
	server_socket = server_input_tag = -1;

	if (Exult_server::try_connect_to_server(static_path) > 0)
		server_input_tag = gtk_timeout_add(50, Read_from_server, this);
	else
		return false;
#endif
	cout << "Connected to server" << endl;
	send_to_server(Exult_server::info);
	set_edit_menu(false, false);
	return true;
	}
