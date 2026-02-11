audgui_pixbuf_request (const char * filename)
{
    const void * data;
    int64_t size;

    aud_art_request_data (filename, & data, & size);
    if (! data)
        return NULL;

    GdkPixbuf * p = audgui_pixbuf_from_data (data, size);

    aud_art_unref (filename);
    return p;
}
