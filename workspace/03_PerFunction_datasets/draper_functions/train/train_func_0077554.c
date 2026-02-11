op_sequenceIncludes(PyObject *seq, PyObject* ob)
{
    if (PyErr_WarnPy3k("operator.sequenceIncludes() is not supported "
                       "in 3.x. Use operator.contains().", 1) < 0)
        return -1;
    return PySequence_Contains(seq, ob);
}
