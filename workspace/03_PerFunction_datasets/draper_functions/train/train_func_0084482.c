text_render_redraw(TextRender *w)
{
    if (!GTK_WIDGET_REALIZED (GTK_WIDGET (w)))
        return;

    gdk_window_invalidate_rect (GTK_WIDGET (w)->window, NULL, FALSE);
}
