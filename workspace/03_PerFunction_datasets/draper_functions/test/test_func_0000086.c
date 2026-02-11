_dict_read(void *data, char *buf, size_t size, size_t *pret)
{
    struct _dict_stream *str = data;

    switch (str->type) {
    case DICTORG_UNKNOWN:
	return DE_UNKNOWN_FORMAT;

    case DICTORG_TEXT:
	return _dict_read_text(str, buf, size, pret);

    case DICTORG_GZIP:
	return DE_GZIP_SEEK;

    case DICTORG_DZIP:
	return _dict_read_dzip(str, buf, size, pret);
    }
    return DE_UNSUPPORTED_FORMAT;
}
