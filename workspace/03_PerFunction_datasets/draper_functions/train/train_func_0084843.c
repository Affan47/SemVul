dumpFcache1(char *prev)
#else
CacheEntry *dumpFcache1(prev)
  char  *prev;
#endif
{
    Entry   **table=Fcache;

    int     low=0;
    int     hi=0;

    CacheEntry  *least=NULL;

	Entry   **p;

	for (p=table; p<&(table[HashTableSize]); p++) {

		CacheEntry *q =(CacheEntry *) *p;

		if ( q != NULL && low==0 ) low = p-table;
		while ( q != NULL ) {
            if (strcmp(q->str,prev) > 0) {
              if (least == NULL) {
                least=q;
              } else {
                if (strcmp(q->str,least->str) < 0) {
                  least=q;
                };
              };
            };
			q = q->next;
		};

		if ( *p != NULL ) hi = p-table;
	}
    return least;
}
