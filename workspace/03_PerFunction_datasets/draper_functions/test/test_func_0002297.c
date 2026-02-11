PyCFunction_GetSelf(PyObject *op)
{
    if (!PyCFunction_Check(op)) {
        PyErr_BadInternalCall();
        return NULL;
    }
    return PyCFunction_GET_SELF(op);
}
