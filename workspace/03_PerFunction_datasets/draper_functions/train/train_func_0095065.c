bg_start_connect(void)
{
    int	tmp;

    if (!bg_server)
	bg_server = server_create(-1);

    set_message("Opening second connection to server...", False);
    if (global.nntp_server[0] != '#')
	tmp = server_open(bg_server, global.serv_addr, 0);
    else
	tmp = server_fork(bg_server, NULL, 0);

    if (tmp < 0) {
	set_message("Failed to open second connection to server!", True);
	server_close(bg_server);
	return False;
    }

    input_id = XtAppAddInput(app_cont, server_get_fd(bg_server),
			     (XtPointer)XtInputReadMask,
			     bg_read_callback, NULL);
    bg_state = BgStateConnWait;

    return True;
}
