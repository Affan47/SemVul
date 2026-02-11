JArray_Type(PyObject *self, PyObject *arg)
{
    PyObject *type_name = NULL, *type;
    char const *name = NULL;

    if (PyType_Check(arg))
    {
        type_name = PyObject_GetAttrString(arg, "__name__");
        if (!type_name)
            return NULL;
    }
    else if (PyString_Check(arg))
    {
        type_name = arg;
        Py_INCREF(type_name);
    }
    else if (PyFloat_Check(arg))
    {
        type_name = NULL;
        name = "double";
    }
    else
    {
        PyObject *arg_type = (PyObject *) arg->ob_type;

        type_name = PyObject_GetAttrString(arg_type, "__name__");
        if (!type_name)
            return NULL;
    }

    if (type_name != NULL)
    {
        name = PyString_AsString(type_name);
        if (!name)
        {
            Py_DECREF(type_name);
            return NULL;
        }
    }

    if (!strcmp(name, "object"))
        type = (PyObject *) &jarray_jobject.type_object;
    else if (!strcmp(name, "string"))
        type = (PyObject *) &jarray_jstring.type_object;
    else if (!strcmp(name, "bool"))
        type = (PyObject *) &jarray_jboolean.type_object;
    else if (!strcmp(name, "byte"))
        type = (PyObject *) &jarray_jbyte.type_object;
    else if (!strcmp(name, "char"))
        type = (PyObject *) &jarray_jchar.type_object;
    else if (!strcmp(name, "double"))
        type = (PyObject *) &jarray_jdouble.type_object;
    else if (!strcmp(name, "float"))
        type = (PyObject *) &jarray_jfloat.type_object;
    else if (!strcmp(name, "int"))
        type = (PyObject *) &jarray_jint.type_object;
    else if (!strcmp(name, "long"))
        type = (PyObject *) &jarray_jlong.type_object;
    else if (!strcmp(name, "short"))
        type = (PyObject *) &jarray_jshort.type_object;
    else
    {
        PyErr_SetObject(PyExc_ValueError, arg);
        Py_XDECREF(type_name);

        return NULL;
    }

    Py_INCREF(type);
    Py_XDECREF(type_name);

    return type;
}
