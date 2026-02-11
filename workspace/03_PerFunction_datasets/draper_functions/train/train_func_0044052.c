pysqlite_connection_set_progress_handler(pysqlite_Connection* self, PyObject* args, PyObject* kwargs)
{
    PyObject* progress_handler;
    int n;

    static char *kwlist[] = { "progress_handler", "n", NULL };

    if (!pysqlite_check_thread(self) || !pysqlite_check_connection(self)) {
        return NULL;
    }

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi:set_progress_handler",
                                      kwlist, &progress_handler, &n)) {
        return NULL;
    }

    if (progress_handler == Py_None) {

        sqlite3_progress_handler(self->db, 0, 0, (void*)0);
    } else {
        sqlite3_progress_handler(self->db, n, _progress_handler, progress_handler);
        if (PyDict_SetItem(self->function_pinboard, progress_handler, Py_None) == -1)
            return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}
