initgtkvnc(void)
{
    PyObject *m, *d;

    init_pygobject ();

    m = Py_InitModule ("gtkvnc", gtkvnc_functions);
    if (PyErr_Occurred())
        Py_FatalError("can't init module");

    d = PyModule_GetDict (m);
    if (PyErr_Occurred())
        Py_FatalError("can't get dict");

    gtkvnc_add_constants(m, "VNC_DISPLAY_");
    gtkvnc_register_classes (d);

    if (PyErr_Occurred ()) {
        Py_FatalError ("can't initialise module vnc");
    }
}
