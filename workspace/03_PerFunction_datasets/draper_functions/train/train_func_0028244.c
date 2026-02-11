als_init(int4 elemsize, int4 (*comp)(), int4 nlist, struct al_head *plist,
         LIST *ald)
{
	char		*curr;
	char		*next;
	char		*prev;
	int4		n;


	ald->al_elemsize = elemsize;
	ald->al_comp = comp;
	ald->al_ltop = 0;
	ald->al_lbottom = 0;
	ald->al_ftop = plist;


	curr = (char *) plist;
	prev = curr;

	for (n = 0; n < nlist; ++n) {
		next = curr + elemsize + sizeof(struct al_head);
		((struct al_head *) curr)->al_next = (struct al_head *) next;
		prev = curr;
		curr = next;
	}

	((struct al_head *) prev)->al_next = 0;
	return(ald);
}
