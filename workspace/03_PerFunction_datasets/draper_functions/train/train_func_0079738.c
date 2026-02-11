_pickle_Unpickler_find_class_impl(UnpicklerObject *self, PyObject *module_name, PyObject *global_name)

{
    PyObject *global;
    PyObject *modules_dict;
    PyObject *module;
    _Py_IDENTIFIER(modules);


    if (self->proto < 3 && self->fix_imports) {
        PyObject *key;
        PyObject *item;
        PickleState *st = _Pickle_GetGlobalState();


        key = PyTuple_Pack(2, module_name, global_name);
        if (key == NULL)
            return NULL;
        item = PyDict_GetItemWithError(st->name_mapping_2to3, key);
        Py_DECREF(key);
        if (item) {
            if (!PyTuple_Check(item) || PyTuple_GET_SIZE(item) != 2) {
                PyErr_Format(PyExc_RuntimeError,
                             "_compat_pickle.NAME_MAPPING values should be "
                             "2-tuples, not %.200s", Py_TYPE(item)->tp_name);
                return NULL;
            }
            module_name = PyTuple_GET_ITEM(item, 0);
            global_name = PyTuple_GET_ITEM(item, 1);
            if (!PyUnicode_Check(module_name) ||
                !PyUnicode_Check(global_name)) {
                PyErr_Format(PyExc_RuntimeError,
                             "_compat_pickle.NAME_MAPPING values should be "
                             "pairs of str, not (%.200s, %.200s)",
                             Py_TYPE(module_name)->tp_name,
                             Py_TYPE(global_name)->tp_name);
                return NULL;
            }
        }
        else if (PyErr_Occurred()) {
            return NULL;
        }


        item = PyDict_GetItemWithError(st->import_mapping_2to3, module_name);
        if (item) {
            if (!PyUnicode_Check(item)) {
                PyErr_Format(PyExc_RuntimeError,
                             "_compat_pickle.IMPORT_MAPPING values should be "
                             "strings, not %.200s", Py_TYPE(item)->tp_name);
                return NULL;
            }
            module_name = item;
        }
        else if (PyErr_Occurred()) {
            return NULL;
        }
    }

    modules_dict = _PySys_GetObjectId(&PyId_modules);
    if (modules_dict == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "unable to get sys.modules");
        return NULL;
    }

    module = PyDict_GetItemWithError(modules_dict, module_name);
    if (module == NULL) {
        if (PyErr_Occurred())
            return NULL;
        module = PyImport_Import(module_name);
        if (module == NULL)
            return NULL;
        global = getattribute(module, global_name, self->proto >= 4);
        Py_DECREF(module);
    }
    else {
        global = getattribute(module, global_name, self->proto >= 4);
    }
    return global;
}
