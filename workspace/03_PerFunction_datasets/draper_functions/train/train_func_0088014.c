desk_button_press_event(GtkWidget * widget, GdkEventButton * event, desk *d)
{
    ENTER;
    if (event->type == GDK_BUTTON_PRESS && event->button == 3
          && event->state & GDK_CONTROL_MASK) {
        RET(FALSE);
    }
    DBG("s=%d\n", d->no);
    Xclimsg(GDK_ROOT_WINDOW(), a_NET_CURRENT_DESKTOP, d->no, 0, 0, 0, 0);
    RET(TRUE);
}
