gen_dealloc(PyGenObject *gen)
{
    PyObject *self = (PyObject *) gen;

    _PyObject_GC_UNTRACK(gen);

    if (gen->gi_weakreflist != NULL)
        PyObject_ClearWeakRefs(self);

    _PyObject_GC_TRACK(self);

    if (gen->gi_frame != NULL && gen->gi_frame->f_stacktop != NULL) {

        Py_TYPE(gen)->tp_del(self);
        if (self->ob_refcnt > 0)
            return;
    }

    _PyObject_GC_UNTRACK(self);
    Py_CLEAR(gen->gi_frame);
    Py_CLEAR(gen->gi_code);
    PyObject_GC_Del(gen);
}
