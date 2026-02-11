find_variable(catalog_t * context, const char *name,
			   const char *newvalue)
{
    int r = 0;
    int hash = (int) strlen(name);
    struct varnames *current, *last, *newp;
    hash =
	((unsigned char) (name[0]) + (unsigned char) (name[hash - 1]) +
	 hash) % (unsigned int) CHASHMAX;
    current = last = context->root[hash];
    while (current != NULL) {
	last = current;
	r = strcmp(current->name, name);
	if (!r) {
	    if (newvalue != NULL) {
		free(current->value);
		current->value = mystrdup(newvalue);
	    }
	    return (current->value);
	}
	if (r > 0)
	    current = current->left;
	else
	    current = current->right;
    }

    if (newvalue == NULL)
	return (NULL);
    newp = (struct varnames *) calloc(1, sizeof(struct varnames));
    newp->name = mystrdup(name);
    newp->value = mystrdup(newvalue);

    newp->left = NULL;
    newp->right = NULL;
    if (last == NULL) {
	context->root[hash] = newp;
    } else {
	if (r > 0)
	    last->left = newp;
	else
	    last->right = newp;
    }
    return (newp->value);
}
