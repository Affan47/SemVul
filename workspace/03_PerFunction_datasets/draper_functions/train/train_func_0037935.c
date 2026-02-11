gwy_selection_set_object_default(GwySelection *selection,
                                 gint i,
                                 const gdouble *data)
{
    guint object_size, max_len;

    gwy_debug("%p: setting object %d, n=%d", selection, i, selection->n);
    if (i < 0)
        i = selection->n;
    object_size = GWY_SELECTION_GET_CLASS(selection)->object_size;
    max_len = selection->objects->len/object_size;
    g_return_val_if_fail(i < max_len, -1);
    if (i > selection->n) {
        g_warning("Disontinuous selections are not supported.  "
                  "Moving object to first feasible position.");
        i = MIN(selection->n, max_len-1);
    }

    selection->n = MAX(selection->n, i+1);
    memcpy(selection->objects->data + i*object_size*sizeof(gdouble), data,
           object_size*sizeof(gdouble));

    g_signal_emit(selection, selection_signals[CHANGED], 0, i);
    return i;
}
