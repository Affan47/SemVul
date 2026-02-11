ListItem_New(const char *listname)
{
	ListItemObject *item;
	item = PyObject_New(ListItemObject, &ListItem_Type);
	if (item != NULL) {

		item->listname = listname;
		item->dict = PyDict_New();
		if (item->dict == NULL) {
			Py_DECREF(item);
			item = NULL;
		}
	}
	return (PyObject *) item;
}
