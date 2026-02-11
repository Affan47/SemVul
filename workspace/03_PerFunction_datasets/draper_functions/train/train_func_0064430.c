local_new(PyTypeObject *type, PyObject *args, PyObject *kw)
{
    localobject *self;
    PyObject *wr;
    static PyMethodDef wr_callback_def = {
        "_localdummy_destroyed", (PyCFunction) _localdummy_destroyed, METH_O
    };

    if (type->tp_init == PyBaseObject_Type.tp_init
        && ((args && PyObject_IsTrue(args))
        || (kw && PyObject_IsTrue(kw)))) {
        PyErr_SetString(PyExc_TypeError,
                  "Initialization arguments are not supported");
        return NULL;
    }

    self = (localobject *)type->tp_alloc(type, 0);
    if (self == NULL)
        return NULL;

    Py_XINCREF(args);
    self->args = args;
    Py_XINCREF(kw);
    self->kw = kw;
    self->key = PyUnicode_FromFormat("thread.local.%p", self);
    if (self->key == NULL)
        goto err;

    self->dummies = PyDict_New();
    if (self->dummies == NULL)
        goto err;


    wr = PyWeakref_NewRef((PyObject *) self, NULL);
    if (wr == NULL)
        goto err;
    self->wr_callback = PyCFunction_NewEx(&wr_callback_def, wr, NULL);
    Py_DECREF(wr);
    if (self->wr_callback == NULL)
        goto err;

    if (_local_create_dummy(self) == NULL)
        goto err;

    return (PyObject *)self;

  err:
    Py_DECREF(self);
    return NULL;
}
