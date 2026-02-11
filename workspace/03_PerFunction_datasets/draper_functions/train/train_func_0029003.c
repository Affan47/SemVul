gtk_bgbox_set_bg_root(GtkWidget *widget, GtkBgboxPrivate *priv)
{
    priv = GTK_BGBOX_GET_PRIVATE (widget);

    ENTER;
    priv->pixmap = fb_bg_get_xroot_pix_for_win(priv->bg, widget);
    if (!priv->pixmap || priv->pixmap ==  GDK_NO_BG) {

        priv->pixmap = NULL;
        gtk_style_set_background(widget->style, widget->window, widget->state);
        gtk_widget_queue_draw_area(widget, 0, 0,
              widget->allocation.width, widget->allocation.height);
        DBG("no root pixmap was found\n");
        RET();
    }
    if (priv->alpha)
        fb_bg_composite(priv->pixmap, widget->style->black_gc,
              priv->tintcolor, priv->alpha);
    gdk_window_set_back_pixmap(widget->window, priv->pixmap, FALSE);
    RET();
}
