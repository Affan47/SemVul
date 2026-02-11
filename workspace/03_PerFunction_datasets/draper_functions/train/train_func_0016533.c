py_format_get_keys(struct event_format *ef)
{
	PyObject *list;
	struct format_field *f;

	list = PyList_New(0);

	for (f = ef->format.fields; f; f = f->next) {
		if (PyList_Append(list, PyString_FromString(f->name))) {
			Py_DECREF(list);
			return NULL;
		}
	}

	return list;
}
