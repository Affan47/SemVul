make_descriptor(jlong value)
{
    t_descriptor *self = (t_descriptor *)
        PY_TYPE(ConstVariableDescriptor).tp_alloc(&PY_TYPE(ConstVariableDescriptor), 0);

    if (self)
    {
        self->access.value = PyLong_FromLongLong((long long) value);
        self->flags = DESCRIPTOR_VALUE;
    }

    return (PyObject *) self;
}
