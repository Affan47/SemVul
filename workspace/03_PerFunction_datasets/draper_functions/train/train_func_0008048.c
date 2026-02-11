Module_hexchat_hook_unload(PyObject *self, PyObject *args, PyObject *kwargs)
{
	PyObject *callback;
	PyObject *userdata = Py_None;
	PyObject *plugin;
	Hook *hook;
	char *kwlist[] = {"callback", "userdata", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O|O:hook_unload",
					 kwlist, &callback, &userdata))
		return NULL;

	plugin = Plugin_GetCurrent();
	if (plugin == NULL)
		return NULL;
	if (!PyCallable_Check(callback)) {
		PyErr_SetString(PyExc_TypeError, "callback is not callable");
		return NULL;
	}

	hook = Plugin_AddHook(HOOK_UNLOAD, plugin, callback, userdata, NULL, NULL);
	if (hook == NULL)
		return NULL;

	return PyLong_FromVoidPtr(hook);
}
