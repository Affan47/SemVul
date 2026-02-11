_wrap_vnc_display_set_credential(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "type", "data", NULL };
    int type, ret;
    char *data;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"is:Vnc.Display.set_credential", kwlist, &type, &data))
        return NULL;

    ret = vnc_display_set_credential(VNC_DISPLAY(self->obj), type, data);

    return PyBool_FromLong(ret);

}
