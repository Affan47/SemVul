boxObject(PyTypeObject *type, PyObject *arg, java::lang::Object *obj)
{
    int result = boxJObject(type, arg, obj);

    if (result <= 0)
        return result;

    if (obj != NULL)
    {
        if (PyString_Check(arg) || PyUnicode_Check(arg))
        {
            *obj = p2j(arg);
            if (PyErr_Occurred())
                return -1;
        }
        else if (arg == Py_True)
            *obj = *Boolean::TRUE;
        else if (arg == Py_False)
            *obj = *Boolean::FALSE;
        else if (PyInt_Check(arg))
        {
            long ln = PyInt_AS_LONG(arg);
            int n = (int) ln;

            if (ln != (long) n)
                *obj = Long((jlong) ln);
            else
                *obj = Integer((jint) n);
        }
        else if (PyLong_Check(arg))
            *obj = Long((jlong) PyLong_AsLongLong(arg));
        else if (PyFloat_Check(arg))
            *obj = Double((jdouble) PyFloat_AS_DOUBLE(arg));
        else
            return -1;
    }
    else if (!(PyString_Check(arg) || PyUnicode_Check(arg) ||
               arg == Py_True || arg == Py_False ||
               PyInt_Check(arg) || PyLong_Check(arg) ||
               PyFloat_Check(arg)))
        return -1;

    return 0;
}
