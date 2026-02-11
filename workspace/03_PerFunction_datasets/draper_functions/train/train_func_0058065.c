devinfo_search_path ()
{
	bool devinfo_path_defined = false;
        std::string spath_env (Glib::getenv (devinfo_env_variable_name, devinfo_path_defined));

	if (devinfo_path_defined) {
		return spath_env;
	}

	SearchPath spath (ardour_data_search_path());
	spath.add_subdirectory_to_paths(devinfo_dir_name);

	return spath;
}
