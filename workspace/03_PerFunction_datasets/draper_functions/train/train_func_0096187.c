Pickler_get_pers_func(Picklerobject *p)
{
    if (p->pers_func == NULL)
        PyErr_SetString(PyExc_AttributeError, "persistent_id");
    else
        Py_INCREF(p->pers_func);
    return p->pers_func;
}
