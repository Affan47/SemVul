lookup_call (const char *p)
{
	struct call_list *clp;

	for (clp = call_cache; clp; clp = clp->next) {
		if (strcmp (p, clp->callname) == 0) {
			return;
		}
	}
	clp = cobc_malloc (sizeof (struct call_list));
	clp->callname = p;
	clp->next = call_cache;
	call_cache = clp;
}
