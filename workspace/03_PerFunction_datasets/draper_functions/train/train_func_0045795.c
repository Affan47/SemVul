cfgtree_walk(ap_directive_t *dir)
{


    PyObject *list = PyList_New(0);
    if (!list)
        return PyErr_NoMemory();

    while (dir) {

        PyObject *t = Py_BuildValue("(s, s)", dir->directive, dir->args);
        if (!t)
            return PyErr_NoMemory();

        PyList_Append(list, t);

        Py_DECREF(t);

        if (dir->first_child) {

            PyObject *child = cfgtree_walk(dir->first_child);
            if (!child)
                return PyErr_NoMemory();

            PyList_Append(list, child);

            Py_DECREF(child);

        }

        dir = dir->next;
    }

    return list;
}
