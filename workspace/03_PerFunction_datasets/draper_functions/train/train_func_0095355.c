jl_array_grow_end(jl_array_t *a, size_t inc)
{

    size_t alen = a->length;
    if ((alen + inc) > a->maxsize - a->offset) {
        size_t newlen = a->maxsize==0 ? (inc<4?4:inc) : a->maxsize*2;
        while ((alen + inc) > newlen - a->offset)
            newlen *= 2;
        char *newdata = array_new_buffer(a, newlen);
        size_t es = a->elsize;
        newdata += (a->offset*es);
        size_t anb = alen*es;
        memcpy(newdata, (char*)a->data, anb);
        if (es == 1) {
            memset(newdata + anb, 0, (newlen-a->offset-alen)*es);
        }
        a->maxsize = newlen;
        a->data = newdata;
    }
    a->length += inc; a->nrows += inc;
}
