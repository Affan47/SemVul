gwy_hmarker_box_button_release(GtkWidget *widget,
                               GdkEventButton *event)
{
    GwyMarkerBox *mbox;
    gdouble pos;
    gboolean ghost;
    gint x, y;


    mbox = GWY_MARKER_BOX(widget);
    if (event->button != 1 || !mbox->button)
        return FALSE;

    x = (gint)event->x;
    y = (gint)event->y;
    ghost = (y > 3*widget->allocation.height/2 + 2
             || y < -widget->allocation.height/2 - 2);

    mbox->ghost = FALSE;
    mbox->button = 0;

    if (ghost) {
        if (gwy_marker_box_remove_marker(mbox, mbox->selected))
            return FALSE;
    }
    if (!mbox->moved)
        return FALSE;

    pos = (x - mbox->offset)/(widget->allocation.width - 1.0);
    gwy_marker_box_set_marker_position(mbox, mbox->selected,
                                       CLAMP(pos, 0.0, 1.0));

    return FALSE;
}
