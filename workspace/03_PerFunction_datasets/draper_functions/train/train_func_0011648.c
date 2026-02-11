globalroot(void *addr) {
	Root *root;
#if ASSERTIONS
	for (root = globalrootlist; root != NULL; root = root->next)
		assert(root->p != addr);
#endif
	root = ealloc(sizeof (Root));
	root->p = addr;
	root->next = globalrootlist;
	globalrootlist = root;
}
