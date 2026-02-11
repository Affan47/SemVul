AuParser_add_callback(AuParser *self, PyObject *args)
{
    PyObject *func;
    PyObject *user_data;

    if (!PyArg_ParseTuple(args, "O|O:add_callback", &func, &user_data)) return NULL;
    if (!PyFunction_Check(func)) {
        PyErr_SetString(PyExc_ValueError, "callback must be a function");
        return NULL;
    }
    PARSER_CHECK;

    {
        CallbackData *cb;

        cb = PyMem_New(CallbackData, 1);
        if (cb == NULL)
            return PyErr_NoMemory();
        cb->py_AuParser = self;
        cb->func = func;
        cb->user_data = user_data;
        Py_INCREF(cb->func);
        Py_XINCREF(cb->user_data);
        auparse_add_callback(self->au, auparse_callback, cb, callback_data_destroy);
}

    Py_RETURN_NONE;
}
