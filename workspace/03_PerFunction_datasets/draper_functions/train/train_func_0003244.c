mem_store(krb5_storage *sp, const void *data, size_t size)
{
    mem_storage *s = (mem_storage*)sp->data;
    if(size > (size_t)(s->base + s->size - s->ptr))
	size = s->base + s->size - s->ptr;
    memmove(s->ptr, data, size);
    sp->seek(sp, size, SEEK_CUR);
    return size;
}
