_wrap_goo_canvas_request_item_redraw(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "bounds", "is_static", NULL };
    PyObject *py_bounds;
    int is_static;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!i:GooCanvas.request_item_redraw", kwlist, &PyGooCanvasBounds_Type, &py_bounds, &is_static))
        return NULL;

    goo_canvas_request_item_redraw(GOO_CANVAS(self->obj), (py_bounds == NULL)? NULL : &((PyGooCanvasBounds *) py_bounds)->bounds, is_static);

    Py_INCREF(Py_None);
    return Py_None;
}
