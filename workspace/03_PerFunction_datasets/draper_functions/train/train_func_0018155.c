proxy_richcompare(PyObject *proxy, PyObject *v, int op)
{
    UNWRAP(proxy);
    UNWRAP(v);
    return PyObject_RichCompare(proxy, v, op);
}
