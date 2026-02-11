super_getattro(PyObject *self, PyObject *name)
{
    superobject *su = (superobject *)self;
    int skip = su->obj_type == NULL;

    if (!skip) {


        skip = (PyUnicode_Check(name) &&
                PyUnicode_GET_LENGTH(name) == 9 &&
                _PyUnicode_CompareWithId(name, &PyId___class__) == 0);
    }

    if (!skip) {
        PyObject *mro, *res, *tmp, *dict;
        PyTypeObject *starttype;
        descrgetfunc f;
        Py_ssize_t i, n;

        starttype = su->obj_type;
        mro = starttype->tp_mro;

        if (mro == NULL)
            n = 0;
        else {
            assert(PyTuple_Check(mro));
            n = PyTuple_GET_SIZE(mro);
        }
        for (i = 0; i < n; i++) {
            if ((PyObject *)(su->type) == PyTuple_GET_ITEM(mro, i))
                break;
        }
        i++;
        res = NULL;


        Py_INCREF(mro);
        for (; i < n; i++) {
            tmp = PyTuple_GET_ITEM(mro, i);
            if (PyType_Check(tmp))
                dict = ((PyTypeObject *)tmp)->tp_dict;
            else
                continue;
            res = PyDict_GetItem(dict, name);
            if (res != NULL) {
                Py_INCREF(res);
                f = Py_TYPE(res)->tp_descr_get;
                if (f != NULL) {
                    tmp = f(res,


                        (su->obj == (PyObject *)
                                    su->obj_type
                            ? (PyObject *)NULL
                            : su->obj),
                        (PyObject *)starttype);
                    Py_DECREF(res);
                    res = tmp;
                }
                Py_DECREF(mro);
                return res;
            }
        }
        Py_DECREF(mro);
    }
    return PyObject_GenericGetAttr(self, name);
}
