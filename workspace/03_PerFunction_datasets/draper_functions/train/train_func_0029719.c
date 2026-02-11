PyMethod_New(PyObject *func, PyObject *self, PyObject *klass)
{
    register PyMethodObject *im;
    im = free_list;
    if (im != NULL) {
        free_list = (PyMethodObject *)(im->im_self);
        PyObject_INIT(im, &PyMethod_Type);
        numfree--;
    }
    else {
        im = PyObject_GC_New(PyMethodObject, &PyMethod_Type);
        if (im == NULL)
            return NULL;
    }
    im->im_weakreflist = NULL;
    Py_INCREF(func);
    im->im_func = func;
    Py_XINCREF(self);
    im->im_self = self;
    Py_XINCREF(klass);
    im->im_class = klass;
    _PyObject_GC_TRACK(im);
    return (PyObject *)im;
}
