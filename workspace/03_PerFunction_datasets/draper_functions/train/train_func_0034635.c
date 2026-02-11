ekg_user_groups(ekg_userObj * self)
{
	session_t * s = session_find((const char *) self->session);
	userlist_t * u = userlist_find(s, self->name);
	struct ekg_group *gl;
	PyObject *list;
	int len = LIST_COUNT2(u->groups);

	list = PyList_New(len);
	len = 0;

	for (gl = u->groups; gl; gl = gl->next) {
		struct ekg_group *g = gl;
		PyList_SetItem(list, len, PyString_FromString(g->name));
		len++;
	}
	Py_INCREF(list);
	return list;
}
