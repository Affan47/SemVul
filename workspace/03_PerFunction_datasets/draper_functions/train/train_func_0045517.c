load_inst(Unpicklerobject *self)
{
    PyObject *tup, *class=0, *obj=0, *module_name, *class_name;
    Py_ssize_t i, len;
    char *s;

    if ((i = marker(self)) < 0) return -1;

    if ((len = self->readline_func(self, &s)) < 0) return -1;
    if (len < 2) return bad_readline();
    module_name = PyString_FromStringAndSize(s, len - 1);
    if (!module_name)  return -1;

    if ((len = self->readline_func(self, &s)) >= 0) {
        if (len < 2) return bad_readline();
        if ((class_name = PyString_FromStringAndSize(s, len - 1))) {
            class = find_class(module_name, class_name,
                               self->find_class);
            Py_DECREF(class_name);
        }
    }
    Py_DECREF(module_name);

    if (! class) return -1;

    if ((tup=Pdata_popTuple(self->stack, i))) {
        obj = Instance_New(class, tup);
        Py_DECREF(tup);
    }
    Py_DECREF(class);

    if (! obj) return -1;

    PDATA_PUSH(self->stack, obj, -1);
    return 0;
}
