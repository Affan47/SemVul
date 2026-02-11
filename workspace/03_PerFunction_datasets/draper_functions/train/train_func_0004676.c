gplp_load_base (GOPluginLoader *loader, GOErrorInfo **ret_error)
{
	static gchar const *python_file_extensions[] = {"py", "pyc", "pyo", NULL};

	GnmPythonPluginLoader *loader_python = GNM_PYTHON_PLUGIN_LOADER (loader);
	gchar const **file_ext;
	GnmPython *py_object;
	GnmPyInterpreter *py_interpreter_info;
	gchar *full_module_file_name = NULL;
	FILE *f;
	GOPlugin *plugin = go_plugin_loader_get_plugin (loader);
	GOErrorInfo *open_error = NULL;
	PyObject *modules, *main_module, *main_module_dict;

	GO_INIT_RET_ERROR_INFO (ret_error);
	g_object_set_data (G_OBJECT (plugin), "python-loader", loader);

	py_object = gnm_python_object_get (ret_error);
	if (py_object == NULL)
		return;
	py_interpreter_info = gnm_python_new_interpreter (py_object, plugin);
	if (py_interpreter_info == NULL) {
		*ret_error = go_error_info_new_str (_("Cannot create new Python interpreter."));
		gnm_python_clear_error_if_needed (py_object);
		g_object_unref (py_object);
		return;
	}

	for (file_ext = python_file_extensions; *file_ext != NULL; file_ext++) {
		gchar *file_name = g_strconcat (
			loader_python->module_name, ".", *file_ext, NULL);
		gchar *path = g_build_filename (
			go_plugin_get_dir_name (plugin),
			file_name, NULL);
		g_free (file_name);
		if (g_file_test (path, G_FILE_TEST_EXISTS)) {
			full_module_file_name = path;
			break;
		} else
			g_free (path);
	}
	if (full_module_file_name == NULL) {
		*ret_error = go_error_info_new_printf (
		             _("Module \"%s\" doesn't exist."),
		             loader_python->module_name);
		gnm_python_destroy_interpreter (py_object, py_interpreter_info);
		g_object_unref (py_object);
		return;
	}
	f = gnumeric_fopen_error_info (full_module_file_name, "r", &open_error);
	g_free (full_module_file_name);
	if (f == NULL) {
		*ret_error = open_error;
		gnm_python_destroy_interpreter (py_object, py_interpreter_info);
		g_object_unref (py_object);
		return;
	}

	if (PyRun_SimpleFile (f, loader_python->module_name) != 0) {
		(void) fclose (f);
		*ret_error = go_error_info_new_printf (
		             _("Execution of module \"%s\" failed."),
		             loader_python->module_name);
		gnm_python_destroy_interpreter (py_object, py_interpreter_info);
		g_object_unref (py_object);
		return;
	}
	(void) fclose (f);

	modules = PyImport_GetModuleDict ();
	g_return_if_fail (modules != NULL);
	main_module = PyDict_GetItemString (modules, (char *) "__main__");
	g_return_if_fail (main_module != NULL);
	main_module_dict = PyModule_GetDict (main_module);
	g_return_if_fail (main_module_dict != NULL);
	loader_python->py_object = py_object;
	loader_python->py_interpreter_info = py_interpreter_info;
	loader_python->main_module = main_module;
	loader_python->main_module_dict = main_module_dict;
}
