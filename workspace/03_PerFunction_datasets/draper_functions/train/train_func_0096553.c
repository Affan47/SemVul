_set_bool(const char *name, int *target, PyObject *src, int dflt)
{
    if (src == NULL)
        *target = dflt;
    else
        *target = PyObject_IsTrue(src);
    return 0;
}
