_wrap_goo_canvas_item_get_requested_area(PyGObject *self,
                                         PyObject *args,
                                         PyObject *kwargs)
{
    static char     *kwlist[] = { "cr", NULL };
    GooCanvasBounds bounds;
    PycairoContext  *cr;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     "O!:GooCanvasItem.get_requested_area",
                                     kwlist, &PycairoContext_Type, &cr))
        return NULL;

    goo_canvas_item_get_requested_area(GOO_CANVAS_ITEM(self->obj),
                                             cr->ctx, &bounds);

    return pygoo_canvas_bounds_new(&bounds);
}
