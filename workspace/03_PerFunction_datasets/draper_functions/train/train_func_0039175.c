dstrputc(dstr_t *ds, int c)
{
    if (ds->len +1 >= ds->alloc) {
        ds->alloc *= 2;
        ds->data = realloc(ds->data, ds->alloc);
    }
    ds->data[ds->len++] = c;
    ds->data[ds->len] = '\0';
}
