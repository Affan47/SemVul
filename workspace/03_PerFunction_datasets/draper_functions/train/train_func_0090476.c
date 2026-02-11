get_dimensions(GArray * axes)
{
    unsigned int i;
    double width;
    GArray *axis, *out_array = NULL;

    gwy_debug("start");
    if (axes == NULL)
        return NULL;

    out_array = g_array_new(FALSE, FALSE, sizeof(double));
    for (i = 0; i < axes->len; i++) {
        axis = g_array_index(axes, GArray *, i);
        if (axis->len > 1) {
            width = (g_array_index(axis, double, 1) - g_array_index(axis, double, 0))
                * axis->len;
            out_array = g_array_append_val(out_array, width);
            gwy_debug("Start: %e, step: %e, count: %d, width: %e",
                      g_array_index(axis, double, 0),
                      g_array_index(axis, double, 1) - g_array_index(axis, double, 0),
                      axis->len,
                      width
                     );
        } else {
            g_array_free(out_array, TRUE);
            gwy_debug("Axis values count lesser than 2");
            return NULL;
        }


    }
    return out_array;

}
