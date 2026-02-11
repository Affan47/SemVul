al_free(LIST *ald)
{
	struct al_head	*curr;
	struct al_head	*next;


	if (ald == NULL) {
	  return 0;
	}

	curr = ald->al_ltop;

	while (curr != 0) {
		next = curr->al_next;
		free((char *) curr);
		curr = next;
	}

	free((char *) ald);
	return(0);
}
