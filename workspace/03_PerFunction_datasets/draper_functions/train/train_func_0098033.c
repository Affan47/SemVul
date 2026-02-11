request_handler (Glib::IOCondition ioc)
{


	if (ioc & ~IO_IN) {
		_main_loop->quit ();
	}

	if (ioc & IO_IN) {
		request_channel.drain ();


		handle_ui_requests ();
	}

	return true;
}
