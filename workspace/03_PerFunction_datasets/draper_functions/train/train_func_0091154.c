main (int argc, char *argv[])
{
	GError *error = NULL;

	gtk_init (&argc, &argv);
	libgoffice_init ();
	go_plugins_init (NULL, NULL, NULL, NULL, TRUE, GO_TYPE_PLUGIN_LOADER_MODULE);
	Loader::Init (Application::GetDefaultApplication ());
	gcu::Element::Init ();
	in_channel = g_io_channel_unix_new (fileno (stdin));
	g_io_add_watch (in_channel, G_IO_IN, io_func, &error);
	gtk_main ();
	g_io_channel_unref (in_channel);
	map <void*, ChemComp*>::iterator i, end = components.end ();
	for (i = components.begin (); i != end; i++)
		delete (*i).second;
	components.clear ();
	return 0;
}
