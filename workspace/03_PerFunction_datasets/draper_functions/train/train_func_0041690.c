ctxmanager_restore_global(PyDecContextManagerObject *self,
                          PyObject *args UNUSED)
{
    PyObject *ret;

    ret = PyDec_SetCurrentContext(NULL, self->global);
    if (ret == NULL) {
        return NULL;
    }
    Py_DECREF(ret);

    Py_RETURN_NONE;
}
