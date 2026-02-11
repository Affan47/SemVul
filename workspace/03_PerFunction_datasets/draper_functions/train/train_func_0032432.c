_wrap_goo_canvas_points__get_coords(PyObject *self, void *closure)
{
    gdouble     *coords;
    int         num_points, i;
    PyObject    *ret = Py_None;

    num_points = pyg_boxed_get(self, GooCanvasPoints)->num_points;
    coords = pyg_boxed_get(self, GooCanvasPoints)->coords;

    if (num_points > 0) {
        ret = PyList_New(num_points);

        for (i = 0; i < num_points; i ++) {
            PyObject *py_temp = Py_BuildValue("dd", coords[2*i], coords[2*i + 1]);
            PyList_SetItem(ret, i, py_temp);
        }
        return ret;
    }
    Py_INCREF(ret);
    return ret;
}
