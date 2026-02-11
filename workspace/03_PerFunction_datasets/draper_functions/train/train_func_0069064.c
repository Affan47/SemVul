gwy_axis_finalize(GObject *object)
{
    GwyAxis *axis;

    g_return_if_fail(GWY_IS_AXIS(object));

    axis = GWY_AXIS(object);

    g_string_free(axis->label_text, TRUE);
    g_array_free(axis->mjticks, TRUE);
    g_array_free(axis->miticks, TRUE);
    if (axis->mjpubticks)
        g_array_free(axis->mjpubticks, TRUE);

    gwy_object_unref(axis->unit);
    gwy_object_unref(axis->gc);

    if (axis->par.major_font)
        pango_font_description_free(axis->par.major_font);
    if (axis->par.label_font)
        pango_font_description_free(axis->par.label_font);

    G_OBJECT_CLASS(gwy_axis_parent_class)->finalize(object);
}
