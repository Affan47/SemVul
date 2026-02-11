PyMemoryView_FromBuffer(Py_buffer *info)
{
    PyMemoryViewObject *mview;

    mview = (PyMemoryViewObject *)
        PyObject_GC_New(PyMemoryViewObject, &PyMemoryView_Type);
    if (mview == NULL)
        return NULL;
    mview->base = NULL;
    dup_buffer(&mview->view, info);


    _PyObject_GC_TRACK(mview);
    return (PyObject *)mview;
}
