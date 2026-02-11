io_write(void *data, const char *buf, size_t size, size_t *pret)
{
    struct _iostr *p = data;
    if (dico_stream_write(p->out, buf, size)) {
	p->last_err = p->out;
	return dico_stream_last_error(p->out);
    }
    *pret = size;
    return 0;
}
