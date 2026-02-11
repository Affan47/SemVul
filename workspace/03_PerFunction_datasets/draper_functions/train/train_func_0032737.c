arrayiter_setstate(arrayiterobject *it, PyObject *state)
{
    Py_ssize_t index = PyLong_AsSsize_t(state);
    if (index == -1 && PyErr_Occurred())
        return NULL;
    if (index < 0)
        index = 0;
    else if (index > Py_SIZE(it->ao))
        index = Py_SIZE(it->ao);
    it->index = index;
    Py_RETURN_NONE;
}
