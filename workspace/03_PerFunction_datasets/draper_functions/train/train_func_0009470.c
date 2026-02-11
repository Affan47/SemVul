list_subscript(PyListObject* self, PyObject* item)
{
    if (PyIndex_Check(item)) {
        Py_ssize_t i;
        i = PyNumber_AsSsize_t(item, PyExc_IndexError);
        if (i == -1 && PyErr_Occurred())
            return NULL;
        if (i < 0)
            i += PyList_GET_SIZE(self);
        return list_item(self, i);
    }
    else if (PySlice_Check(item)) {
        Py_ssize_t start, stop, step, slicelength, cur, i;
        PyObject* result;
        PyObject* it;
        PyObject **src, **dest;

        if (PySlice_GetIndicesEx(item, Py_SIZE(self),
                         &start, &stop, &step, &slicelength) < 0) {
            return NULL;
        }

        if (slicelength <= 0) {
            return PyList_New(0);
        }
        else if (step == 1) {
            return list_slice(self, start, stop);
        }
        else {
            result = PyList_New(slicelength);
            if (!result) return NULL;

            src = self->ob_item;
            dest = ((PyListObject *)result)->ob_item;
            for (cur = start, i = 0; i < slicelength;
                 cur += (size_t)step, i++) {
                it = src[cur];
                Py_INCREF(it);
                dest[i] = it;
            }

            return result;
        }
    }
    else {
        PyErr_Format(PyExc_TypeError,
                     "list indices must be integers, not %.200s",
                     item->ob_type->tp_name);
        return NULL;
    }
}
