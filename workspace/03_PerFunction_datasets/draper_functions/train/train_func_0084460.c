getFriendlyList(PyObject *self, PyObject *args) {
    PyObject *list;
    object *ob;

    list = PyList_New(0);
    ob = cf_friendlylist_get_first();
    while (ob) {
        PyList_Append(list, Crossfire_Object_wrap(ob));
        ob = cf_friendlylist_get_next(ob);
   }
   return list;
}
