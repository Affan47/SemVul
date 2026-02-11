PyEval_GetFuncName(PyObject *func)
{
    if (PyMethod_Check(func))
        return PyEval_GetFuncName(PyMethod_GET_FUNCTION(func));
    else if (PyFunction_Check(func))
        return _PyUnicode_AsString(((PyFunctionObject*)func)->func_name);
    else if (PyCFunction_Check(func))
        return ((PyCFunctionObject*)func)->m_ml->ml_name;
    else
        return func->ob_type->tp_name;
}
