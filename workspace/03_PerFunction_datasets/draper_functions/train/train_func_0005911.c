_PyAccu_Accumulate(_PyAccu *acc, PyObject *unicode)
{
    Py_ssize_t nsmall;
    assert(PyUnicode_Check(unicode));

    if (PyList_Append(acc->small, unicode))
        return -1;
    nsmall = PyList_GET_SIZE(acc->small);


    if (nsmall < 100000)
        return 0;
    return flush_accumulator(acc);
}
