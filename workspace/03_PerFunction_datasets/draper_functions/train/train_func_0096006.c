_wrap_goo_canvas_item_model_get_transform(PyGObject *self)
{
    PyObject        *matrix;
    cairo_matrix_t  transform = {0,};
    gboolean        res;

    res = goo_canvas_item_model_get_transform(GOO_CANVAS_ITEM_MODEL(self->obj),
                                              &transform);

    if (!res) {
        Py_INCREF(Py_None);
        return Py_None;
    }

    matrix = PycairoMatrix_FromMatrix(&transform);
    return matrix;
}
