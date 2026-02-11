_wrap_goo_canvas_item_remove_child(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "child", NULL };
    int child_num;
    PyObject *py_child;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:GooCanvasItem.remove_child", kwlist, &py_child))
        return NULL;

    if (PyInt_Check(py_child))
        child_num = PyInt_AsLong(py_child);
    else {
        if (!PyObject_IsInstance(py_child, (PyObject *) &PyGooCanvasItem_Type)) {
            PyErr_SetString(PyExc_TypeError, "argument must be integer or goocanvas.Item");
            return NULL;
        }
        child_num = goo_canvas_item_find_child(GOO_CANVAS_ITEM(self->obj), GOO_CANVAS_ITEM(pygobject_get(py_child)));
        if (child_num == -1) {
            PyErr_SetString(PyExc_ValueError, "child not found");
            return NULL;
        }
    }
    goo_canvas_item_remove_child(GOO_CANVAS_ITEM(self->obj), child_num);

    Py_INCREF(Py_None);
    return Py_None;
}
