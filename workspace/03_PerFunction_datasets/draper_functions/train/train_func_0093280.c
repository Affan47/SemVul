PythonMwc2eqStdErr(PyObject * UNUSED(self), PyObject * args)
{

    PyObject *pyCubeInfo = NULL;
    float r = 0.0f;
    cubeinfo ci;

    if (!PyArg_ParseTuple(args, "|fO:mwc2eq_stderr", &r, &pyCubeInfo))
        return NULL;

    GetMatchStateCubeInfo(&ci, &ms);

    if (pyCubeInfo && PyToCubeInfo(pyCubeInfo, &ci))
        return NULL;

    return PyFloat_FromDouble(se_mwc2eq(r, &ci));
}
