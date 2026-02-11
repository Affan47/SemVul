PyInit_time(void)
{
    PyObject *m;
    m = PyModule_Create(&timemodule);
    if (m == NULL)
        return NULL;


    PyInit_timezone(m);

    if (!initialized) {
        PyStructSequence_InitType(&StructTimeType,
                                  &struct_time_type_desc);


        PyStructSequence_InitType(&ClockInfoType, &ClockInfo_desc);
        Py_INCREF(&ClockInfoType);
        PyModule_AddObject(m, "clock_info", (PyObject*)&ClockInfoType);

#ifdef MS_WINDOWS
        winver.dwOSVersionInfoSize = sizeof(winver);
        if (!GetVersionEx((OSVERSIONINFO*)&winver)) {
            Py_DECREF(m);
            PyErr_SetFromWindowsErr(0);
            return NULL;
        }
#endif
    }
    Py_INCREF(&StructTimeType);
    PyModule_AddObject(m, "struct_time", (PyObject*) &StructTimeType);
    initialized = 1;
    return m;
}
