PyImport_GetImporter(PyObject *path) {
    PyObject *importer=NULL, *path_importer_cache=NULL, *path_hooks=NULL;

    if ((path_importer_cache = PySys_GetObject("path_importer_cache"))) {
        if ((path_hooks = PySys_GetObject("path_hooks"))) {
            importer = get_path_importer(path_importer_cache,
                                         path_hooks, path);
        }
    }
    Py_XINCREF(importer);
    return importer;
}
