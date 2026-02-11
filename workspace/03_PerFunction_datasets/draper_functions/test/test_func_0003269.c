mp3_set_title (source_t *source)
{
    const char streamtitle[] = "StreamTitle='";
    const char streamurl[] = "StreamUrl='";
    size_t size;
    unsigned char len_byte;
    refbuf_t *p;
    unsigned int len = sizeof(streamtitle) + 2;
    mp3_state *source_mp3 = source->format->_state;


    thread_mutex_lock (&source_mp3->url_lock);


    if (source_mp3->url_artist)
        len += strlen (source_mp3->url_artist);
    if (source_mp3->url_title)
        len += strlen (source_mp3->url_title);
    if (source_mp3->url_artist && source_mp3->url_title)
        len += 3;
    if (source_mp3->inline_url)
    {
        char *end = strstr (source_mp3->inline_url, "';");
        if (end)
            len += end - source_mp3->inline_url+2;
    }
    else if (source_mp3->url)
        len += strlen (source_mp3->url) + strlen (streamurl) + 2;
#define MAX_META_LEN 255*16
    if (len > MAX_META_LEN)
    {
        thread_mutex_unlock (&source_mp3->url_lock);
        WARN1 ("Metadata too long at %d chars", len);
        return;
    }

    len_byte = (len-1) / 16 + 1;


    size = len_byte * 16 + 1;

    p = refbuf_new (size);
    if (p)
    {
        mp3_state *source_mp3 = source->format->_state;
        int r;

        memset (p->data, '\0', size);
        if (source_mp3->url_artist && source_mp3->url_title)
            r = snprintf (p->data, size, "%c%s%s - %s';", len_byte, streamtitle,
                    source_mp3->url_artist, source_mp3->url_title);
        else
            r = snprintf (p->data, size, "%c%s%s';", len_byte, streamtitle,
                    source_mp3->url_title);
        if (r > 0)
        {
            if (source_mp3->inline_url)
            {
                char *end = strstr (source_mp3->inline_url, "';");
                int urllen = size;
                if (end) urllen = end - source_mp3->inline_url + 2;
                if (size-r > urllen)
                    snprintf (p->data+r, size-r, "StreamUrl='%s';", source_mp3->inline_url+11);
            }
            else if (source_mp3->url)
                snprintf (p->data+r, size-r, "StreamUrl='%s';", source_mp3->url);
        }
        DEBUG1 ("shoutcast metadata block setup with %s", p->data+1);
        filter_shoutcast_metadata (source, p->data, size);

        refbuf_release (source_mp3->metadata);
        source_mp3->metadata = p;
    }
    thread_mutex_unlock (&source_mp3->url_lock);
}
