table_subscript(tableobject *self, register PyObject *key)
{
    char *k;
    const apr_array_header_t *ah;
    apr_table_entry_t *elts;
    register int i;
    PyObject *list;

    if (key && !PyString_CheckExact(key)) {
        PyErr_SetString(PyExc_TypeError,
                        "table keys must be strings");
        return NULL;
    }
    k = PyString_AsString(key);


    list = PyList_New(0);
    if (!list)
        return NULL;

    ah = apr_table_elts (self->table);
    elts = (apr_table_entry_t *) ah->elts;

    i = ah->nelts;

    while (i--)
        if (elts[i].key) {
            if (apr_strnatcasecmp(elts[i].key, k) == 0) {
                PyObject *v = NULL;
                if (elts[i].val != NULL) {
                    v = PyString_FromString(elts[i].val);
                } else {
                    v = Py_None;
                    Py_INCREF(v);
                }

                PyList_Insert(list, 0, v);
                Py_DECREF(v);
            }
        }


    if (PyList_Size(list) == 0) {
        Py_DECREF(list);
        PyErr_SetObject(PyExc_KeyError, key);
        return NULL;
    }


    if (PyList_Size(list) == 1) {

        PyObject *v = PyList_GetItem(list, 0);
        Py_INCREF(v);
        Py_DECREF(list);
        return v;
    }


    return list;
}
