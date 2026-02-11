python_build_user(char * session, const char * name)
{
	ekg_userObj *pyuser;
	char buf[100];
	session_t *s;
	userlist_t *u;

	debug("[python] checking for user '%s' in session '%s'\n", name, session);

	s = session_find(session);
	u = userlist_find(s, name);

	if (!u) {
		snprintf(buf, 99, "Can't find user '%s'", name);
		PyErr_SetString(PyExc_KeyError, buf);
		return NULL;
	}

	debug("[python] Building object for user '%s'\n", name);
	pyuser = PyObject_New(ekg_userObj, &ekg_user_type);
	pyuser->name = xstrdup(name);
	pyuser->session = xstrdup(session);
	Py_INCREF(pyuser);
	return (PyObject *)pyuser;
}
