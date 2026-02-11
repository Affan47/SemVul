zipimporter_get_data(PyObject *obj, PyObject *args)
{
    ZipImporter *self = (ZipImporter *)obj;
    PyObject *path, *key;
    PyObject *toc_entry;
    Py_ssize_t path_start, path_len, len;

    if (!PyArg_ParseTuple(args, "U:zipimporter.get_data", &path))
        return NULL;

#ifdef ALTSEP
    path = _PyObject_CallMethodId(path, &PyId_replace, "CC", ALTSEP, SEP);
    if (!path)
        return NULL;
#else
    Py_INCREF(path);
#endif
    if (PyUnicode_READY(path) == -1)
        goto error;

    path_len = PyUnicode_GET_LENGTH(path);

    len = PyUnicode_GET_LENGTH(self->archive);
    path_start = 0;
    if (PyUnicode_Tailmatch(path, self->archive, 0, len, -1)
        && PyUnicode_READ_CHAR(path, len) == SEP) {
        path_start = len + 1;
    }

    key = PyUnicode_Substring(path, path_start, path_len);
    if (key == NULL)
        goto error;
    toc_entry = PyDict_GetItem(self->files, key);
    if (toc_entry == NULL) {
        PyErr_SetFromErrnoWithFilenameObject(PyExc_IOError, key);
        Py_DECREF(key);
        goto error;
    }
    Py_DECREF(key);
    Py_DECREF(path);
    return get_data(self->archive, toc_entry);
  error:
    Py_DECREF(path);
    return NULL;
}
