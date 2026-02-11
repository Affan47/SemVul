match_span(MatchObject* self, PyObject* args)
{
    Py_ssize_t index;

    PyObject* index_ = NULL;
    if (!PyArg_UnpackTuple(args, "span", 0, 1, &index_))
        return NULL;

    index = match_getindex(self, index_);

    if (index < 0 || index >= self->groups) {
        PyErr_SetString(
            PyExc_IndexError,
            "no such group"
            );
        return NULL;
    }


    return _pair(self->mark[index*2], self->mark[index*2+1]);
}
