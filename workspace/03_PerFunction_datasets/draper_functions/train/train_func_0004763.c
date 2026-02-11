init ()
{
	if (libpbd_initialized) {
		return true;
	}

	if (!Glib::thread_supported()) {
		Glib::thread_init();
	}

	Gio::init ();

	PBD::ID::init ();

	setup_libpbd_enums ();

	libpbd_initialized = true;
	return true;
}
