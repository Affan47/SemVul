semlock_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    char buffer[256];
    SEM_HANDLE handle = SEM_FAILED;
    int kind, maxvalue, value;
    PyObject *result;
    static char *kwlist[] = {"kind", "value", "maxvalue", NULL};
    static int counter = 0;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "iii", kwlist,
                                     &kind, &value, &maxvalue))
        return NULL;

    if (kind != RECURSIVE_MUTEX && kind != SEMAPHORE) {
        PyErr_SetString(PyExc_ValueError, "unrecognized kind");
        return NULL;
    }

    PyOS_snprintf(buffer, sizeof(buffer), "/mp%ld-%d", (long)getpid(), counter++);

    SEM_CLEAR_ERROR();
    handle = SEM_CREATE(buffer, value, maxvalue);

    if (handle == SEM_FAILED || SEM_GET_LAST_ERROR() != 0)
        goto failure;

    if (SEM_UNLINK(buffer) < 0)
        goto failure;

    result = newsemlockobject(type, handle, kind, maxvalue);
    if (!result)
        goto failure;

    return result;

  failure:
    if (handle != SEM_FAILED)
        SEM_CLOSE(handle);
    mp_SetError(NULL, MP_STANDARD_ERROR);
    return NULL;
}
