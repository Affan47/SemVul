text_render_reserve_utf8buf(TextRender *w, int minlength)
{
    if (w->priv->utf8alloc < minlength)
    {
        w->priv->utf8alloc = minlength*2;
        w->priv->utf8buf = (unsigned char*) g_realloc (w->priv->utf8buf, w->priv->utf8alloc);
    }
}
