get_module_code(ZipImporter *self, char *fullname,
                int *p_ispackage, char **p_modpath)
{
    PyObject *toc_entry;
    char *subname, path[MAXPATHLEN + 1];
    int len;
    struct st_zip_searchorder *zso;

    subname = get_subname(fullname);

    len = make_filename(PyString_AsString(self->prefix), subname, path);
    if (len < 0)
        return NULL;

    for (zso = zip_searchorder; *zso->suffix; zso++) {
        PyObject *code = NULL;

        strcpy(path + len, zso->suffix);
        if (Py_VerboseFlag > 1)
            PySys_WriteStderr("# trying %s%c%s\n",
                              PyString_AsString(self->archive),
                              SEP, path);
        toc_entry = PyDict_GetItemString(self->files, path);
        if (toc_entry != NULL) {
            time_t mtime = 0;
            int ispackage = zso->type & IS_PACKAGE;
            int isbytecode = zso->type & IS_BYTECODE;

            if (isbytecode)
                mtime = get_mtime_of_source(self, path);
            if (p_ispackage != NULL)
                *p_ispackage = ispackage;
            code = get_code_from_data(self, ispackage,
                                      isbytecode, mtime,
                                      toc_entry);
            if (code == Py_None) {


                Py_DECREF(code);
                continue;
            }
            if (code != NULL && p_modpath != NULL)
                *p_modpath = PyString_AsString(
                    PyTuple_GetItem(toc_entry, 0));
            return code;
        }
    }
    PyErr_Format(ZipImportError, "can't find module '%.200s'", fullname);
    return NULL;
}
