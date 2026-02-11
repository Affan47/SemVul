PyFrame_FastToLocals(PyFrameObject *f)
{
    int res;

    assert(!PyErr_Occurred());

    res = PyFrame_FastToLocalsWithError(f);
    if (res < 0)
        PyErr_Clear();
}
