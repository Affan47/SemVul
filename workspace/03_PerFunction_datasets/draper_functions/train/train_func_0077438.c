zipimporter_get_data(PyObject *obj, PyObject *args)
{
    ZipImporter *self = (ZipImporter *)obj;
    char *path;
#ifdef ALTSEP
    char *p, buf[MAXPATHLEN + 1];
#endif
    PyObject *toc_entry;
    Py_ssize_t len;

    if (!PyArg_ParseTuple(args, "s:zipimporter.get_data", &path))
        return NULL;

#ifdef ALTSEP
    if (strlen(path) >= MAXPATHLEN) {
        PyErr_SetString(ZipImportError, "path too long");
        return NULL;
    }
    strcpy(buf, path);
    for (p = buf; *p; p++) {
        if (*p == ALTSEP)
            *p = SEP;
    }
    path = buf;
#endif
    len = PyString_Size(self->archive);
    if ((size_t)len < strlen(path) &&
        strncmp(path, PyString_AsString(self->archive), len) == 0 &&
        path[len] == SEP) {
        path = path + len + 1;
    }

    toc_entry = PyDict_GetItemString(self->files, path);
    if (toc_entry == NULL) {
        PyErr_SetFromErrnoWithFilename(PyExc_IOError, path);
        return NULL;
    }
    return get_data(PyString_AsString(self->archive), toc_entry);
}
