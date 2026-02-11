get_filter(PyObject *category, PyObject *text, Py_ssize_t lineno,
           PyObject *module, PyObject **item)
{
    PyObject *action;
    Py_ssize_t i;
    PyObject *warnings_filters;

    warnings_filters = get_warnings_attr("filters");
    if (warnings_filters == NULL) {
        if (PyErr_Occurred())
            return NULL;
    }
    else {
        Py_DECREF(_filters);
        _filters = warnings_filters;
    }

    if (_filters == NULL || !PyList_Check(_filters)) {
        PyErr_SetString(PyExc_ValueError,
                        MODULE_NAME ".filters must be a list");
        return NULL;
    }


    for (i = 0; i < PyList_GET_SIZE(_filters); i++) {
        PyObject *tmp_item, *action, *msg, *cat, *mod, *ln_obj;
        Py_ssize_t ln;
        int is_subclass, good_msg, good_mod;

        tmp_item = *item = PyList_GET_ITEM(_filters, i);
        if (PyTuple_Size(tmp_item) != 5) {
            PyErr_Format(PyExc_ValueError,
                         MODULE_NAME ".filters item %zd isn't a 5-tuple", i);
            return NULL;
        }


        action = PyTuple_GET_ITEM(tmp_item, 0);
        msg = PyTuple_GET_ITEM(tmp_item, 1);
        cat = PyTuple_GET_ITEM(tmp_item, 2);
        mod = PyTuple_GET_ITEM(tmp_item, 3);
        ln_obj = PyTuple_GET_ITEM(tmp_item, 4);

        good_msg = check_matched(msg, text);
        if (good_msg == -1)
            return NULL;

        good_mod = check_matched(mod, module);
        if (good_mod == -1)
            return NULL;

        is_subclass = PyObject_IsSubclass(category, cat);
        if (is_subclass == -1)
            return NULL;

        ln = PyLong_AsSsize_t(ln_obj);
        if (ln == -1 && PyErr_Occurred())
            return NULL;

        if (good_msg && is_subclass && good_mod && (ln == 0 || lineno == ln))
            return action;
    }

    action = get_default_action();
    if (action != NULL)
        return action;

    PyErr_SetString(PyExc_ValueError,
                    MODULE_NAME ".defaultaction not found");
    return NULL;
}
