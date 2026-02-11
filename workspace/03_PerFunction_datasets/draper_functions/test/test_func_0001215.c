PyInit_xxsubtype(void)
{
    PyObject *m;


    spamdict_type.tp_base = &PyDict_Type;
    if (PyType_Ready(&spamdict_type) < 0)
        return NULL;

    spamlist_type.tp_base = &PyList_Type;
    if (PyType_Ready(&spamlist_type) < 0)
        return NULL;

    m = PyModule_Create(&xxsubtypemodule);
    if (m == NULL)
        return NULL;

    if (PyType_Ready(&spamlist_type) < 0)
        return NULL;
    if (PyType_Ready(&spamdict_type) < 0)
        return NULL;

    Py_INCREF(&spamlist_type);
    if (PyModule_AddObject(m, "spamlist",
                           (PyObject *) &spamlist_type) < 0)
        return NULL;

    Py_INCREF(&spamdict_type);
    if (PyModule_AddObject(m, "spamdict",
                           (PyObject *) &spamdict_type) < 0)
        return NULL;
    return m;
}
