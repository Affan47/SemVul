_wrap_goo_canvas_convert_from_pixels(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "x", "y", NULL };
    gdouble x, y;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"dd:GooCanvas.convert_from_pixels", kwlist, &x, &y))
        return NULL;

    goo_canvas_convert_from_pixels(GOO_CANVAS(self->obj), &x, &y);

    return Py_BuildValue("dd", x, y);
}
