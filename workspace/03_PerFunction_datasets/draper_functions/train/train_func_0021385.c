worklist_pop(worklist_t **wlp)
{
	worklist_t *wl = *wlp;
	reg_t retval;

	if (!wl || !wl->used) {
		fprintf(stderr, "Attempt to pop from empty worklist");
		exit(1);
	}

	retval = wl->entries[--wl->used];

	if (!wl->used) {
		*wlp = wl->next;
		sci_free(wl);
	}

	return retval;
}
