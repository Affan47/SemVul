add_file_to_path (const std::string &path, const std::string file)
{
	std::string result = std::string ("");
	gchar *newpath = g_build_filename (path.c_str(), file.c_str(), NULL);
	if (newpath)
		result = std::string (newpath);
	g_free (newpath);
	return result;
}
