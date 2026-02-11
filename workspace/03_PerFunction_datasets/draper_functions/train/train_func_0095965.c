pygoo_canvas_bounds_tp_new(PyTypeObject *type, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x1", "y1", "x2", "y2", NULL };
    PyGooCanvasBounds *self;
    GooCanvasBounds bounds = {0,};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     "|dddd:goocanvas.Bounds.__init__", kwlist,
                                     &bounds.x1, &bounds.y1, &bounds.x2, &bounds.y2))
        return NULL;

    self = (PyGooCanvasBounds *) PyObject_NEW(PyGooCanvasBounds,
                                              &PyGooCanvasBounds_Type);
    self->bounds = bounds;
    return (PyObject *) self;
}
