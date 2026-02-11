set_sizeof(PySetObject *so)
{
    Py_ssize_t res;

    res = sizeof(PySetObject);
    if (so->table != so->smalltable)
        res = res + (so->mask + 1) * sizeof(setentry);
    return PyLong_FromSsize_t(res);
}
