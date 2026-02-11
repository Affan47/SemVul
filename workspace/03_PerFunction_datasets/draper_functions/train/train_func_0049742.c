treeQ_enqueue(struct treeQelem *treeQ_elptr)
{
	int tep_rc = FSCK_OK;

	if (agg_recptr->treeQ_back == NULL) {

		agg_recptr->treeQ_back = agg_recptr->treeQ_front = treeQ_elptr;
		treeQ_elptr->prev = treeQ_elptr->next = NULL;
	} else {

		treeQ_elptr->next = NULL;
		treeQ_elptr->prev = agg_recptr->treeQ_back;
		agg_recptr->treeQ_back->next = treeQ_elptr;
		agg_recptr->treeQ_back = treeQ_elptr;
	}

	return (tep_rc);
}
