py_GnumericFuncDict_subscript (py_GnumericFuncDict_object *self, PyObject *key)
{
	gchar *fn_name;
	GnmFunc *fn_def;

	if (!PyArg_Parse(key, (char *) "s", &fn_name)) {
		return NULL;
	}

	fn_def = gnm_func_lookup (fn_name, NULL);
	if (fn_def == NULL) {

		PyErr_SetObject (PyExc_KeyError, key);
		return NULL;
	}

	return py_new_GnumericFunc_object (fn_def, NULL);
}
