apprentice_1(struct magic_set *ms, const char *fn, int action,
    struct mlist *mlist)
{
	struct magic *magic = NULL;
	uint32_t nmagic = 0;
	struct mlist *ml;
	int rv = -1;
	int mapped;

	if (magicsize != FILE_MAGICSIZE) {
		file_error(ms, 0, "magic element size %lu != %lu",
		    (unsigned long)sizeof(*magic),
		    (unsigned long)FILE_MAGICSIZE);
		return -1;
	}

	if (action == FILE_COMPILE) {
		rv = apprentice_load(ms, &magic, &nmagic, fn, action);
		if (rv != 0)
			return -1;
		rv = apprentice_compile(ms, &magic, &nmagic, fn);
		free(magic);
		return rv;
	}

#ifndef COMPILE_ONLY
	if ((rv = apprentice_map(ms, &magic, &nmagic, fn)) == -1) {
		if (ms->flags & MAGIC_CHECK)
			file_magwarn(ms, "using regular magic file `%s'", fn);
		rv = apprentice_load(ms, &magic, &nmagic, fn, action);
		if (rv != 0)
			return -1;
	}

	mapped = rv;

	if (magic == NULL) {
		file_delmagic(magic, mapped, nmagic);
		return -1;
	}

	if ((ml = CAST(struct mlist *, malloc(sizeof(*ml)))) == NULL) {
		file_delmagic(magic, mapped, nmagic);
		file_oomem(ms, sizeof(*ml));
		return -1;
	}

	ml->magic = magic;
	ml->nmagic = nmagic;
	ml->mapped = mapped;

	mlist->prev->next = ml;
	ml->prev = mlist->prev;
	ml->next = mlist;
	mlist->prev = ml;

	if (action == FILE_LIST) {
		printf("Binary patterns:\n");
		apprentice_list(mlist, BINTEST);
		printf("Text patterns:\n");
		apprentice_list(mlist, TEXTTEST);
	}

	return 0;
#endif
}
