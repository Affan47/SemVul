_wrap_GooCanvasItem__do_set_transform(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    GooCanvasItemIface *iface;
    static char *kwlist[] = { "self", "matrix", NULL };
    PyGObject *self;
    PyObject *py_matrix;
    cairo_matrix_t *matrix;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!O:GooCanvasItem.set_transform", kwlist, &PyGooCanvasItem_Type, &self, &py_matrix))
        return NULL;
    matrix = &((PycairoMatrix*)(py_matrix))->matrix;
    iface = g_type_interface_peek(g_type_class_peek(pyg_type_from_object(cls)), GOO_TYPE_CANVAS_ITEM);
    if (iface->set_transform)
        iface->set_transform(GOO_CANVAS_ITEM(self->obj), matrix);
    else {
        PyErr_SetString(PyExc_NotImplementedError, "interface method GooCanvasItem.set_transform not implemented");
        return NULL;
    }
    Py_INCREF(Py_None);
    return Py_None;
}
