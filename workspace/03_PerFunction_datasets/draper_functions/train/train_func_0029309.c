pysqlite_statement_dealloc(pysqlite_Statement* self)
{
    if (self->st) {
        Py_BEGIN_ALLOW_THREADS
        sqlite3_finalize(self->st);
        Py_END_ALLOW_THREADS
    }

    self->st = NULL;

    Py_XDECREF(self->sql);

    if (self->in_weakreflist != NULL) {
        PyObject_ClearWeakRefs((PyObject*)self);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}
