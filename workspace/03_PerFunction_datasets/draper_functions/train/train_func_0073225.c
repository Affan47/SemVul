call_method_ret (const string &name, PyObject *args) const
{
    PyObject *result = NULL;

    if (Instance)
    {
        PyObject *tocall = PyObject_GetAttrString (Instance, (char *) name.c_str ());

        if (PyCallable_Check (tocall) == 1)
        {
            result = PyObject_CallObject (tocall, args);
            Py_DECREF (tocall);
        }
#ifdef PY_DEBUG
        python::show_traceback ();
#endif
    }

    return result;
}
