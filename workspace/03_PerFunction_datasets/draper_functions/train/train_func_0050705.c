plugin_init(G3DContext *context)
{
	LeoCadLibrary *library;
	const gchar *libdir;

	libdir = g_getenv("LEOCAD_LIB");
	if(libdir == NULL)
		libdir = "/usr/local/share/leocad";

	library = leocad_library_load(libdir);

	if(library == NULL)
	{
#if DEBUG > 1
		g_warning("LeoCAD: failed to load library");
#endif
		return NULL;
	}

	return library;
}
