_wrap_indicate_listener_server_get_dbusname(PyObject *self)
{
    const gchar *ret;

    ret = indicate_listener_server_get_dbusname(pyg_pointer_get(self, IndicateListenerServer));
    if (ret)
        return PyString_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}
