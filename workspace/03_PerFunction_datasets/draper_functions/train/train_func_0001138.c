poll_unregister(pollObject *self, PyObject *o)
{
    PyObject *key;
    int fd;

    fd = PyObject_AsFileDescriptor( o );
    if (fd == -1)
        return NULL;


    key = PyInt_FromLong(fd);
    if (key == NULL)
        return NULL;

    if (PyDict_DelItem(self->dict, key) == -1) {
        Py_DECREF(key);


        return NULL;
    }

    Py_DECREF(key);
    self->ufd_uptodate = 0;

    Py_INCREF(Py_None);
    return Py_None;
}
