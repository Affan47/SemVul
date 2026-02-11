copy_grouping(char* s)
{
    int i;
    PyObject *result, *val = NULL;

    if (s[0] == '\0')

    return PyList_New(0);

    for (i = 0; s[i] != '\0' && s[i] != CHAR_MAX; i++)
        ;

    result = PyList_New(i+1);
    if (!result)
        return NULL;

    i = -1;
    do {
        i++;
        val = PyInt_FromLong(s[i]);
        if (!val)
            break;
        if (PyList_SetItem(result, i, val)) {
            Py_DECREF(val);
            val = NULL;
            break;
        }
    } while (s[i] != '\0' && s[i] != CHAR_MAX);

    if (!val) {
        Py_DECREF(result);
        return NULL;
    }

    return result;
}
