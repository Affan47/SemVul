gwy_axis_set_si_unit(GwyAxis *axis, GwySIUnit *unit)
{
    if (axis->unit && gwy_si_unit_equal(axis->unit, unit))
        return;

    gwy_serializable_clone(G_OBJECT(unit), G_OBJECT(axis->unit));
    if (GTK_WIDGET_DRAWABLE(axis))
        gtk_widget_queue_draw(GTK_WIDGET(axis));
}
