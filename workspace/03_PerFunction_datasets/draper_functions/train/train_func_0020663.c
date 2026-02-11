delete_song (song * s) {
    if(s->freq_pixbuf)
        gdk_pixbuf_unref(s->freq_pixbuf);
    if(s->color_pixbuf)
        gdk_pixbuf_unref(s->color_pixbuf);
    g_free(s->path);
    g_free(s->title);
    g_free(s->artist);
    g_free(s->album);
    g_free(s);
}
