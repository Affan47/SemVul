ConvertPythonToRowset(PyObject * v)
{
    RowSet *pRow;
    Py_ssize_t row, col;
    int i, j;
    if (PyInt_Check(v)) {
        if (PyInt_AsLong(v) != 0)
            outputerrf(_("unexpected rowset error"));
        return NULL;
    }

    if (!PySequence_Check(v)) {
        outputerrf(_("invalid Python return"));
        return NULL;
    }

    row = PySequence_Size(v);
    col = 0;
    if (row > 0) {
        PyObject *cols = PySequence_GetItem(v, 0);
        if (!PySequence_Check(cols)) {
            outputerrf(_("invalid Python return"));
            return NULL;
        } else
            col = PySequence_Size(cols);
    }

    pRow = MallocRowset((size_t) row, (size_t) col);
    for (i = 0; i < (int) pRow->rows; i++) {
        PyObject *e = PySequence_GetItem(v, i);

        if (!e) {
            outputf(_("Error getting item %d\n"), i);
            continue;
        }

        if (PySequence_Check(e)) {
            for (j = 0; j < (int) pRow->cols; j++) {
                char buf[1024];
                PyObject *e2 = PySequence_GetItem(e, j);

                if (!e2) {
                    outputf(_("Error getting sub item (%d, %d)\n"), i, j);
                    continue;
                }
                if (PyUnicode_Check(e2))
                    strcpy(buf, PyString_AsString(PyUnicode_AsUTF8String(e2)));
                else if (PyString_Check(e2))
                    strcpy(buf, PyString_AsString(e2));
                else if (PyInt_Check(e2) || PyLong_Check(e2)
                         || !StrCaseCmp(e2->ob_type->tp_name, "Decimal"))
                    sprintf(buf, "%d", (int) PyInt_AsLong(e2));
                else if (PyFloat_Check(e2))
                    sprintf(buf, "%.4f", PyFloat_AsDouble(e2));
                else if (e2 == Py_None)
                    sprintf(buf, "[%s]", _("none"));
                else
                    sprintf(buf, "[%s]", _("unknown type"));

                SetRowsetData(pRow, (size_t) i, (size_t) j, buf);

                Py_DECREF(e2);
            }
        } else {
            outputf(_("Item %d is not a list\n"), i);
        }

        Py_DECREF(e);
    }
    return pRow;
}
