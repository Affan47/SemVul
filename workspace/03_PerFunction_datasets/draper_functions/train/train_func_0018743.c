fail(PyObject *self, PyObject *args)
{
	char *name;
	PyObject *rv, *err;

	if (!PyArg_ParseTuple(args, "s:fail", &name))
		return NULL;

	rv = PyLong_FromLong(fiu_fail(name));
	err = PyErr_Occurred();

	if (rv == NULL || err != NULL) {
		Py_XDECREF(rv);
		return NULL;
	}

	return rv;
}
