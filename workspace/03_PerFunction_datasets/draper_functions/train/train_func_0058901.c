_wrap_GooCanvasItemModel__do_get_parent(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    GooCanvasItemModelIface *iface;
    static char *kwlist[] = { "self", NULL };
    PyGObject *self;
    GooCanvasItemModel *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:GooCanvasItemModel.get_parent", kwlist, &PyGooCanvasItemModel_Type, &self))
        return NULL;
    iface = g_type_interface_peek(g_type_class_peek(pyg_type_from_object(cls)), GOO_TYPE_CANVAS_ITEM_MODEL);
    if (iface->get_parent)
        ret = iface->get_parent(GOO_CANVAS_ITEM_MODEL(self->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "interface method GooCanvasItemModel.get_parent not implemented");
        return NULL;
    }

    return pygobject_new((GObject *)ret);
}
