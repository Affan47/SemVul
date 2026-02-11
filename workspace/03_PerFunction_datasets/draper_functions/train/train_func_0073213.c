_wrap_GooCanvasItem__do_request_update(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    GooCanvasItemIface *iface;
    static char *kwlist[] = { "self", NULL };
    PyGObject *self;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:GooCanvasItem.request_update", kwlist, &PyGooCanvasItem_Type, &self))
        return NULL;
    iface = g_type_interface_peek(g_type_class_peek(pyg_type_from_object(cls)), GOO_TYPE_CANVAS_ITEM);
    if (iface->request_update)
        iface->request_update(GOO_CANVAS_ITEM(self->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "interface method GooCanvasItem.request_update not implemented");
        return NULL;
    }
    Py_INCREF(Py_None);
    return Py_None;
}
