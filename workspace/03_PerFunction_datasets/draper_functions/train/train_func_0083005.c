proxy_compare(PyObject *proxy, PyObject *v)
{
    UNWRAP_I(proxy);
    UNWRAP_I(v);
    return PyObject_Compare(proxy, v);
}
