valgrind_view_connect (VgToolView *tool, int sockfd)
{
	VgDefaultView *view = (VgDefaultView *) tool;

	if (view->parser != NULL)
		valgrind_view_disconnect (tool);

	view->parser = vg_error_parser_new (sockfd, recv_error_cb, view);
}
