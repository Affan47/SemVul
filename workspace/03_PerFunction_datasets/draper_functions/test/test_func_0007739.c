IO_get_closed(IOobject *self, void *closure)
{
    PyObject *result = Py_False;

    if (self->buf == NULL)
        result = Py_True;
    Py_INCREF(result);
    return result;
}
