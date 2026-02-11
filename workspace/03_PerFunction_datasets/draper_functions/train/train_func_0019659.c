onkeyup(GtkWidget *widget, GdkEventKey *event, void *data)
{
    int key = event->keyval;
    switch(key)
    {
        case GDK_c:
        case GDK_C:
        case GDK_x:
        case GDK_X:
        case GDK_v:
        case GDK_V:
            if (event->state & GDK_CONTROL_MASK)
                return;
        default:
            break;
    }
    gtk_im_context_filter_keypress(imcontext, event);
}
