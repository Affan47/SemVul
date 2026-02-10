find_or_add_name(Names ** names, const char *str)
{
    unsigned i;

    for (i = 0; i < (*names)->size; i++)
	if (!mystrcasecmp((*names)->names[i], str)) {
	    return i;
	}
    if ((*names)->size == (*names)->max_size) {
	unsigned old_max = (*names)->max_size;
	Names *new = new_names(old_max * 2);
	unsigned i;

	for (i = 0; i < old_max; i++)
	    new->names[i] = (*names)->names[i];
	new->size = old_max;
	myfree((*names)->names, M_NAMES);
	myfree(*names, M_NAMES);
	*names = new;
    }
    (*names)->names[(*names)->size] = str_dup(str);
    return (*names)->size++;
}
