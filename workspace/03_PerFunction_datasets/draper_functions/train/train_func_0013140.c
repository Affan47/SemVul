table_compare(tableobject *a, tableobject *b)
{


    PyObject *ad, *bd;
    int result;

    ad = PyDict_New();
    bd = PyDict_New();

    PyDict_Merge(ad, (PyObject*)a, 0);
    PyDict_Merge(bd, (PyObject*)b, 0);

    result = PyObject_Compare(ad, bd);

    Py_DECREF(ad);
    Py_DECREF(bd);

    return result;
}
