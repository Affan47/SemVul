get_builtin_base_with_dict(PyTypeObject *type)
{
    while (type->tp_base != NULL) {
        if (type->tp_dictoffset != 0 &&
            !(type->tp_flags & Py_TPFLAGS_HEAPTYPE))
            return type;
        type = type->tp_base;
    }
    return NULL;
}
