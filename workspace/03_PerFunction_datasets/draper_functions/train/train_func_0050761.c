ndarray_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    NDArrayObject *nd;

    nd = PyObject_New(NDArrayObject, &NDArray_Type);
    if (nd == NULL)
        return NULL;

    nd->flags = 0;
    nd->head = NULL;
    return (PyObject *)nd;
}
