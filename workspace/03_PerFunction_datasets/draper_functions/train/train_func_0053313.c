cli_map_setvalue(struct cli_map *m, const void* value, int32_t valuesize)
{
    if ((m->valuesize && m->valuesize != valuesize)
	|| m->last_insert >= m->nvalues || m->last_insert < 0)
	return -CL_EARG;
    if (m->valuesize) {
	memcpy((char*)m->u.sized_values + m->last_insert * m->valuesize,
	       value, valuesize);
    } else {
	struct cli_map_value *v = &m->u.unsized_values[m->last_insert];
	if (v->value)
	    free(v->value);
	v->value = cli_malloc(valuesize);
	if (!v->value) {
        cli_errmsg("hashtab.c: Unable to allocate  memory for v->value\n");
        return -CL_EMEM;
    }
	memcpy(v->value, value, valuesize);
	v->valuesize = valuesize;
    }
    return 0;
}
