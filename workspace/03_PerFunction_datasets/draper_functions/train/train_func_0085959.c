make_descriptor(jchar value)
{
    t_descriptor *self = (t_descriptor *)
        PY_TYPE(ConstVariableDescriptor).tp_alloc(&PY_TYPE(ConstVariableDescriptor), 0);

    if (self)
    {
        Py_UNICODE pchar = (Py_UNICODE) value;

        self->access.value = PyUnicode_FromUnicode(&pchar, 1);
        self->flags = DESCRIPTOR_VALUE;
    }

    return (PyObject *) self;
}
