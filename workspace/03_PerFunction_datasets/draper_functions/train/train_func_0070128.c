gplp_func_exec_action (GOPluginService *service,
		       GnmAction const *action,
		       WorkbookControl *wbc,
		       GOErrorInfo **ret_error)
{
	ServiceLoaderDataUI *loader_data;
	PyObject *fn, *ret;

	g_return_if_fail (_PyGObject_API != NULL);

	GO_INIT_RET_ERROR_INFO (ret_error);
	loader_data = g_object_get_data (G_OBJECT (service), "loader_data");
	SWITCH_TO_PLUGIN (go_plugin_service_get_plugin (service));
	fn = PyDict_GetItemString (loader_data->ui_actions, action->id);
	if (fn == NULL) {
		*ret_error = go_error_info_new_printf (_("Unknown action: %s"),
						    action->id);
		return;
	} else if (!PyFunction_Check (fn)) {
		*ret_error = go_error_info_new_printf (
			_("Not a valid function for action: %s"), action->id);
		return;
	}
	ret = PyObject_CallFunction (fn, (char *) "N",
				     py_new_Gui_object (WBC_GTK (wbc)));
	if (ret == NULL) {
		*ret_error = go_error_info_new_str (py_exc_to_string ());
		PyErr_Clear ();
	} else {
		Py_DECREF (ret);
	}
}
