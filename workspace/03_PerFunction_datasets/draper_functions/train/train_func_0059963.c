Crossfire_Object_Reposition(Crossfire_Object *who, PyObject *args) {
    int x, y;

    EXISTCHECK(who);
    if (!PyArg_ParseTuple(args, "ii", &x, &y))
        return NULL;

    cf_object_transfer(who->obj, x, y, 0, NULL);
    Py_INCREF(Py_None);
    return Py_None;
}
