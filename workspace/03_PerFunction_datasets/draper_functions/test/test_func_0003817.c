partial_get_dict(partialobject *pto)
{
    if (pto->dict == NULL) {
        pto->dict = PyDict_New();
        if (pto->dict == NULL)
            return NULL;
    }
    Py_INCREF(pto->dict);
    return pto->dict;
}
