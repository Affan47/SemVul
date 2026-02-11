load_module(char *name, FILE *fp, char *pathname, int type, PyObject *loader)
{
    PyObject *modules;
    PyObject *m;
    int err;


    switch (type) {
    case PY_SOURCE:
    case PY_COMPILED:
        if (fp == NULL) {
            PyErr_Format(PyExc_ValueError,
               "file object required for import (type code %d)",
                         type);
            return NULL;
        }
    }

    switch (type) {

    case PY_SOURCE:
        m = load_source_module(name, pathname, fp);
        break;

    case PY_COMPILED:
        m = load_compiled_module(name, pathname, fp);
        break;

#ifdef HAVE_DYNAMIC_LOADING
    case C_EXTENSION:
        m = _PyImport_LoadDynamicModule(name, pathname, fp);
        break;
#endif

    case PKG_DIRECTORY:
        m = load_package(name, pathname);
        break;

    case C_BUILTIN:
    case PY_FROZEN:
        if (pathname != NULL && pathname[0] != '\0')
            name = pathname;
        if (type == C_BUILTIN)
            err = init_builtin(name);
        else
            err = PyImport_ImportFrozenModule(name);
        if (err < 0)
            return NULL;
        if (err == 0) {
            PyErr_Format(PyExc_ImportError,
                         "Purported %s module %.200s not found",
                         type == C_BUILTIN ?
                                    "builtin" : "frozen",
                         name);
            return NULL;
        }
        modules = PyImport_GetModuleDict();
        m = PyDict_GetItemString(modules, name);
        if (m == NULL) {
            PyErr_Format(
                PyExc_ImportError,
                "%s module %.200s not properly initialized",
                type == C_BUILTIN ?
                    "builtin" : "frozen",
                name);
            return NULL;
        }
        Py_INCREF(m);
        break;

    case IMP_HOOK: {
        if (loader == NULL) {
            PyErr_SetString(PyExc_ImportError,
                            "import hook without loader");
            return NULL;
        }
        m = PyObject_CallMethod(loader, "load_module", "s", name);
        break;
    }

    default:
        PyErr_Format(PyExc_ImportError,
                     "Don't know how to import %.200s (type code %d)",
                      name, type);
        m = NULL;

    }

    return m;
}
