_wrap_goo_canvas_item_get_items_at(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char     *kwlist[] = { "x", "y", "cr", "is_pointer_event",
                                  "parent_is_visible", NULL };
    PyObject        *point_event, *ret, *parent_visible;
    gdouble         x, y;
    GList           *item_list;
    gboolean        is_pointer_event;
    gboolean        parent_is_visible;
    PycairoContext  *cr;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     "ddOOO:get_items_at",
                                     kwlist,
                                     &x, &y, &cr, &point_event,
                                     &parent_visible))
        return NULL;

    is_pointer_event = (PyObject_IsTrue(point_event)) ? TRUE : FALSE;
    parent_is_visible = (PyObject_IsTrue(parent_visible)) ? TRUE : FALSE;

    item_list = goo_canvas_item_get_items_at(GOO_CANVAS_ITEM(self->obj),
                                             x, y, cr->ctx, is_pointer_event,
                                             parent_is_visible, NULL);

    if (!item_list) {
        Py_INCREF (Py_None);
        return Py_None;
    }

    ret = _glist_to_pylist_objs(item_list);
    g_list_free(item_list);
    return ret;
}
