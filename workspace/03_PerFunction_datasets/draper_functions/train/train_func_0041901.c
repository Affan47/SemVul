islice_reduce(isliceobject *lz)
{


    PyObject *stop;
    if (lz->stop == -1) {
        stop = Py_None;
        Py_INCREF(stop);
    } else {
        stop = PyLong_FromSsize_t(lz->stop);
        if (stop == NULL)
            return NULL;
    }
    return Py_BuildValue("O(OnNn)n", Py_TYPE(lz),
        lz->it, lz->next, stop, lz->step,
        lz->cnt);
}
