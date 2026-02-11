get_handler_name(struct HandlerInfo *hinfo)
{
    PyObject *name = hinfo->nameobj;
    if (name == NULL) {
        name = PyUnicode_FromString(hinfo->name);
        hinfo->nameobj = name;
    }
    Py_XINCREF(name);
    return name;
}
