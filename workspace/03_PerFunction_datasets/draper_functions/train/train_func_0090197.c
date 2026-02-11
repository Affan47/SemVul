emem_fetch(krb5_storage *sp, void *data, size_t size)
{
    emem_storage *s = (emem_storage*)sp->data;
    if((size_t)(s->base + s->len - s->ptr) < size)
	size = s->base + s->len - s->ptr;
    memmove(data, s->ptr, size);
    sp->seek(sp, size, SEEK_CUR);
    return size;
}
