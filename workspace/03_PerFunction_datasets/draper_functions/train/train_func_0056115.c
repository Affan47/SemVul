disable(PyObject *self, PyObject *args)
{
	char *name;

	if (!PyArg_ParseTuple(args, "s:disable", &name))
		return NULL;

	return PyLong_FromLong(fiu_disable(name));
}
