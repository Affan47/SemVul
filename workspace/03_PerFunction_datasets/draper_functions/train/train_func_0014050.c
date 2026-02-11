_wrap_keybinder_unbind (PyGObject *self, PyObject *args, PyObject *kwargs)
{
	guint len;
	char *keystring = NULL;
	GSList *iter;

	len = PyTuple_Size(args);
	if (len != 1) {
		PyErr_SetString(PyExc_TypeError, "unbind requires exactly 1 argument");
		return NULL;
	}
	if (!PyArg_ParseTuple(args, "s:keybinder_unbind", &keystring)) {
		return NULL;
	}

	for (iter = HA_List; iter != NULL; iter = iter->next) {
		Handler_and_Args *ha = (Handler_and_Args *) iter->data;

		if (strcmp(keystring, ha->keystring) == 0) {
			keybinder_unbind(keystring, &handler_c_func);
			HA_List = g_slist_remove(HA_List, ha);
			Py_XDECREF(ha->handler);
			Py_XDECREF(ha->args);
			g_free(ha->keystring);
			g_free(ha);

			Py_INCREF(Py_None);
			return Py_None;
		}
	}

	PyErr_SetString(PyExc_KeyError, "bind: keystring is not bound");
	return NULL;
}
