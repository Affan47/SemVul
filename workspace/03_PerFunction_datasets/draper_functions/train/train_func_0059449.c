dict_stream_create(const char *filename, size_t cache_size)
{
    int rc;
    dico_stream_t str;
    struct _dict_stream *s = malloc(sizeof(*s));

    if (!s)
	return NULL;
    rc = dico_stream_create(&str, DICO_STREAM_READ|DICO_STREAM_SEEK, s);
    if (rc) {
	free(s);
	return NULL;
    }

    memset(s, 0, sizeof(*s));
    s->type = DICTORG_UNKNOWN;
    s->cache_size = cache_size ? cache_size : 10;
    s->transport = dico_mapfile_stream_create(filename,
					     DICO_STREAM_READ|DICO_STREAM_SEEK);
    dico_stream_set_open(str, _dict_open);
    dico_stream_set_read(str, _dict_read);
    dico_stream_set_seek(str, _dict_seek);
    dico_stream_set_close(str, _dict_close);
    dico_stream_set_destroy(str, _dict_destroy);
    dico_stream_set_error_string(str, _dict_strerror);

    return str;
}
