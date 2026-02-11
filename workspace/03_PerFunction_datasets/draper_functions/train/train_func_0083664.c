gtk_bgbox_set_background(GtkWidget *widget, int bg_type, guint32 tintcolor, gint alpha)
{
    GtkBgboxPrivate *priv;

    ENTER;
    if (!(GTK_IS_BGBOX (widget)))
        RET();

    priv = GTK_BGBOX_GET_PRIVATE (widget);
    DBG("widget=%p bg_type old:%d new:%d\n", widget, priv->bg_type, bg_type);
    if (priv->pixmap) {
        g_object_unref(priv->pixmap);
        priv->pixmap = NULL;
    }
    priv->bg_type = bg_type;
    if (priv->bg_type == BG_STYLE) {
        gtk_style_set_background(widget->style, widget->window, widget->state);
        if (priv->sid) {
            g_signal_handler_disconnect(priv->bg, priv->sid);
            priv->sid = 0;
        }
        if (priv->bg) {
            g_object_unref(priv->bg);
            priv->bg = NULL;
        }
    } else {
        if (!priv->bg)
            priv->bg = fb_bg_get_for_display();
        if (!priv->sid)
            priv->sid = g_signal_connect(G_OBJECT(priv->bg), "changed", G_CALLBACK(gtk_bgbox_bg_changed), widget);

        if (priv->bg_type == BG_ROOT) {
            priv->tintcolor = tintcolor;
            priv->alpha = alpha;
            gtk_bgbox_set_bg_root(widget, priv);
        } else if (priv->bg_type == BG_INHERIT) {
            gtk_bgbox_set_bg_inherit(widget, priv);
        }
    }
    gtk_widget_queue_draw(widget);
    g_object_notify(G_OBJECT (widget), "style");

    DBG("queue draw all %p\n", widget);
    RET();
}
