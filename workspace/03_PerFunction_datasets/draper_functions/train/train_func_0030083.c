make_Zreplacement(PyObject *object, PyObject *tzinfoarg)
{
    PyObject *temp;
    PyObject *tzinfo = get_tzinfo_member(object);
    PyObject *Zreplacement = PyUnicode_FromStringAndSize(NULL, 0);
    _Py_IDENTIFIER(replace);

    if (Zreplacement == NULL)
        return NULL;
    if (tzinfo == Py_None || tzinfo == NULL)
        return Zreplacement;

    assert(tzinfoarg != NULL);
    temp = call_tzname(tzinfo, tzinfoarg);
    if (temp == NULL)
        goto Error;
    if (temp == Py_None) {
        Py_DECREF(temp);
        return Zreplacement;
    }

    assert(PyUnicode_Check(temp));


    Py_DECREF(Zreplacement);
    Zreplacement = _PyObject_CallMethodId(temp, &PyId_replace, "ss", "%", "%%");
    Py_DECREF(temp);
    if (Zreplacement == NULL)
        return NULL;
    if (!PyUnicode_Check(Zreplacement)) {
        PyErr_SetString(PyExc_TypeError,
                        "tzname.replace() did not return a string");
        goto Error;
    }
    return Zreplacement;

  Error:
    Py_DECREF(Zreplacement);
    return NULL;
}
