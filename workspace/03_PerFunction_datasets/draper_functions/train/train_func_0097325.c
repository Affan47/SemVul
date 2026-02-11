_PyGen_Finalize(PyObject *self)
{
    PyGenObject *gen = (PyGenObject *)self;
    PyObject *res;
    PyObject *error_type, *error_value, *error_traceback;

    if (gen->gi_frame == NULL || gen->gi_frame->f_stacktop == NULL)

        return;


    PyErr_Fetch(&error_type, &error_value, &error_traceback);

    res = gen_close(gen, NULL);

    if (res == NULL)
        PyErr_WriteUnraisable(self);
    else
        Py_DECREF(res);


    PyErr_Restore(error_type, error_value, error_traceback);
}
