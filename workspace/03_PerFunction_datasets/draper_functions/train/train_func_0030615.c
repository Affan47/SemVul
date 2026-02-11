_Cpool_self() {
	struct Cpool_t *current = NULL;
	int             i;
	int             cid;


	Cthread_init();


	if ((cid = _Cthread_self()) < 0) {
		return(-1);
	}


	current = &Cpool;
	while ((current = current->next) != NULL) {
		for (i = 0; i < current->nbelem; i++) {
			if (current->cid[i] == cid) {
				return(current->poolnb);
			}
		}
	}


	return(-1);
}
