hash_delnode (hlist_t **ha, U_CHAR *key, int nkey) {

	int hash;
	hlist_t *t;
	hlist_t *t_prev;


	hash  = (int) ( ntable_m * mrand ( foldkey(key, nkey) ) );


	if (NULL==ha[hash]) return 0;


	for(t = ha[hash]; t; t_prev = t, t = t->next) {

		if (t->nkey==nkey && ! memcmp(t->key, key, nkey))  {

			if (t->data)  free(t->data);
			free(t->key);

			if (t == ha[hash]) ha[hash] = t->next;
			else t_prev->next = t->next;

			free((void *) t);
			return 1;
		}
	}


	return 0;
}
