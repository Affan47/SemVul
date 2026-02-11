hash_getlist (hlist_t **ha, int *cp) {

	int hash;
	hlist_t *t;
	hlist_t **list = NULL;

	*cp = 0;

	for (hash = 0; hash <ntable_m; hash++) {
	t = ha[hash];
	    if ( t != NULL ) {
		  while ( t != NULL ) {
		  list = (hlist_t **) realloc(list,((*cp)+1)*sizeof(hlist_t *));
		  memcpy(list+(*cp),&t,sizeof(hlist_t *));
		  t = t->next;
		  (*cp)++;
		  }
	    }
	}
	return list;
}
