class_traverse(PyClassObject *o, visitproc visit, void *arg)
{
    Py_VISIT(o->cl_bases);
    Py_VISIT(o->cl_dict);
    Py_VISIT(o->cl_name);
    Py_VISIT(o->cl_getattr);
    Py_VISIT(o->cl_setattr);
    Py_VISIT(o->cl_delattr);
    return 0;
}
