text_render_destroy (GtkObject *object)
{
    g_return_if_fail (object != NULL);
    g_return_if_fail (IS_TEXT_RENDER (object));

    TextRender *w = TEXT_RENDER (object);

    if (w->priv)
    {
        g_free (w->priv->fixed_font_name);
        w->priv->fixed_font_name = NULL;

        if (w->priv->v_adjustment)
            g_object_unref (w->priv->v_adjustment);
        w->priv->v_adjustment = NULL;

        if (w->priv->h_adjustment)
            g_object_unref (w->priv->h_adjustment);
        w->priv->h_adjustment = NULL;

        g_free (w->priv->encoding);
        w->priv->encoding = NULL;

        text_render_free_font(w);

        text_render_free_data(w);

        g_free (w->priv->utf8buf);
        w->priv->utf8buf = NULL;

        g_free (w->priv);
        w->priv = NULL;
    }

    if (GTK_OBJECT_CLASS (parent_class)->destroy)
        (* GTK_OBJECT_CLASS (parent_class)->destroy) (object);
}
