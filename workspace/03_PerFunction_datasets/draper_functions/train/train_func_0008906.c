cli_map_getvalue(struct cli_map *m)
{
    if (m->last_find < 0 || m->last_find >= m->nvalues)
	return NULL;
    if (m->valuesize)
	return (char*)m->u.sized_values + m->last_find*m->valuesize;
    return m->u.unsized_values[m->last_find].value;
}
