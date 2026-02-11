gnm_py_interpreter_get_name (GnmPyInterpreter *interpreter)
{
	g_return_val_if_fail (IS_GNM_PY_INTERPRETER (interpreter), NULL);

	if (interpreter->plugin != NULL) {
		return go_plugin_get_name (interpreter->plugin);
	} else {
		return _("Default interpreter");
	}
}
