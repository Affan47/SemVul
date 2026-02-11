ekg_cmd_echo(PyObject * self, PyObject * args)
{
	char *str = NULL;
	int quiet = 0;

	if (!PyArg_ParseTuple(args, "s", &str)) {
		return NULL;
	}
	printq("generic", str);

	Py_INCREF(Py_None);
	return Py_None;
}
