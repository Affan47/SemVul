text_render_button_release(GtkWidget *widget, GdkEventButton *event)
{
    TextRender *w;

    g_return_val_if_fail (widget != NULL, FALSE);
    g_return_val_if_fail (IS_TEXT_RENDER (widget), FALSE);
    g_return_val_if_fail (event != NULL, FALSE);

    w = TEXT_RENDER (widget);

    g_return_val_if_fail (w->priv->pixel_to_offset!=NULL, FALSE);

    if (w->priv->button == event->button)
    {
        gtk_grab_remove (widget);
        w->priv->button = 0;

        w->priv->marker_end = w->priv->pixel_to_offset(w, (int)event->x, (int)event->y, FALSE);
        text_render_redraw(w);
    }

    return FALSE;
}
