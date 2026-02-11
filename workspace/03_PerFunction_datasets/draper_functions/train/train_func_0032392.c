HasHelp ()
{
	if (!HelpBrowser.length () || !HelpFilename.length ())
		return false;
	GFile *file = g_file_new_for_uri (HelpFilename.c_str ());
	bool exists = g_file_query_exists (file, NULL);
	g_object_unref (file);
	return exists;
}
