newsemlockobject(PyTypeObject *type, SEM_HANDLE handle, int kind, int maxvalue)
{
    SemLockObject *self;

    self = PyObject_New(SemLockObject, type);
    if (!self)
        return NULL;
    self->handle = handle;
    self->kind = kind;
    self->count = 0;
    self->last_tid = 0;
    self->maxvalue = maxvalue;
    return (PyObject*)self;
}
