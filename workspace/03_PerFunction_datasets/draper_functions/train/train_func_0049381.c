set_callback (PyObject *cb, PyObject *args)
{
    if (callback) delete callback;
    callback = new py_callback (cb, args);
}
