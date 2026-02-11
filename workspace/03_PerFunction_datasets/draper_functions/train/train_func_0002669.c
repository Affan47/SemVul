find_file_in_path (const Path& path, const string& filename, string& resulting_path)
{
	for (vector<string>::const_iterator i = path.dirs().begin(); i != path.dirs().end(); ++i) {
		resulting_path = Glib::build_filename ((*i), filename);
		if (g_access (resulting_path.c_str(), R_OK) == 0) {
			g_message ("File %s found in Path : %s\n", resulting_path.c_str(),
					path.path_string().c_str());
			return true;
		}
	}

	g_warning ("%s : Could not locate file %s in path %s\n", G_STRLOC, filename.c_str(),
			path.path_string().c_str());

	return false;
}
