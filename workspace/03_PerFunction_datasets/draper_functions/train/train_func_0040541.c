mergegroups(void)
{
    struct nglist *l, *la;
    size_t count = 0;

#ifdef CHECKGROUPORDER
    checkgrouporder();
#endif
    l = newgroup;
    while (l) {
	count++;
	l = l->next;
    }

    active = (struct newsgroup *)critrealloc((char *)active,
					     (1 + count +
					      activesize) *
					     sizeof(struct newsgroup),
					     "reallocating active");

    l = newgroup;
    count = activesize;
    while (l) {
	la = l;
	newsgroup_copy(active + count, l->entry);
	l = l->next;
	count++;
	free(la->entry);
	free(la);
    }
    newgroup = NULL;
    active[count].name = NULL;

    activesize = count;
    qsort(active, activesize, sizeof(struct newsgroup), &compactive);
    validateactive();
}
