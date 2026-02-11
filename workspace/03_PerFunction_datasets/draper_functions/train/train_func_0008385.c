JID_init(JID *self, PyObject *args, PyObject *kwargs)
{
	char *str;
	char *d;
	char *r;

	self->local = NULL;
	self->domain = NULL;
	self->resource = NULL;

	if (!PyArg_ParseTuple(args, "s", &str))
		return -1;


	if (strncmp("jabber:", str, 7) == 0) str += 7;
	if (strncmp("xmpp:", str, 5) == 0) str += 5;

	d = strchr (str, '@');
	r = strchr(str, '/');
	if (d) {
		self->local = Py_BuildValue("s#", str, d - str);
		str = d + 1;
	} else {
		Py_INCREF(Py_None);
		self->local = Py_None;
	}
	if (r) {
		self->resource = Py_BuildValue("s", r + 1);
		self->domain = Py_BuildValue("s#", str, r - str);
	} else {
		Py_INCREF(Py_None);
		self->resource = Py_None;
		self->domain = Py_BuildValue("s", str);
	}

	return 0;
}
