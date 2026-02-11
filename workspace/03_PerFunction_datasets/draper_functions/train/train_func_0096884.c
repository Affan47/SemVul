gtop_proc_signal (PyObject *self, PyObject *args)
{
    glibtop_proc_signal buf;
    PyObject *d;
    guint pid;

    if (!PyArg_ParseTuple (args, "I", &pid))
        return NULL;

    glibtop_get_proc_signal (&buf, pid);

    d = PyDict_New ();

    my_dict_add_and_decref (d, "signal",    build_128bit_long(buf.signal));
    my_dict_add_and_decref (d, "blocked",   build_128bit_long(buf.blocked));
    my_dict_add_and_decref (d, "sigignore", build_128bit_long(buf.sigignore));
    my_dict_add_and_decref (d, "sigcatch",  build_128bit_long(buf.sigcatch));

    return _struct_new (d);
}
