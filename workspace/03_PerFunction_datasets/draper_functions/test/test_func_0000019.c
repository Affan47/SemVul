Callback_Timer(void *userdata)
{
	Hook *hook = (Hook *) userdata;
	PyObject *retobj;
	int ret = 0;
	PyObject *plugin;

	plugin = hook->plugin;

	BEGIN_PLUGIN(hook->plugin);

	retobj = PyObject_CallFunction(hook->callback, "(O)", hook->userdata);

	if (retobj) {
		ret = PyObject_IsTrue(retobj);
		Py_DECREF(retobj);
	} else {
		PyErr_Print();
	}


	if (ret == 0)
		Plugin_RemoveHook(plugin, hook);

	END_PLUGIN(plugin);

	return ret;
}
