Crossfire_Map_RichCompare(Crossfire_Map *left, Crossfire_Map *right, int op) {
    int result;
    if (!left
        || !right
        || !PyObject_TypeCheck((PyObject*)left, &Crossfire_MapType)
        || !PyObject_TypeCheck((PyObject*)right, &Crossfire_MapType)) {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }
    result = Map_InternalCompare(left, right);

    if (result == -1 && PyErr_Occurred())
        return NULL;

    switch (op) {
        case Py_EQ:
            result = (result == 0);
            break;
        case Py_NE:
            result = (result != 0);
            break;
        case Py_LE:
            result = (result <= 0);
            break;
        case Py_GE:
            result = (result >= 0);
            break;
        case Py_LT:
            result = (result == -1);
            break;
        case Py_GT:
            result = (result == 1);
            break;
    }
    return PyBool_FromLong(result);
}
