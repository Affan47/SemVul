dtreeQ_dequeue(struct dtreeQelem **dtreeQ_elptr)
{
	int dQd_rc = FSCK_OK;

	*dtreeQ_elptr = agg_recptr->dtreeQ_front;

	if (agg_recptr->dtreeQ_back == agg_recptr->dtreeQ_front) {

		agg_recptr->dtreeQ_back = agg_recptr->dtreeQ_front = NULL;
	} else {

		agg_recptr->dtreeQ_front = agg_recptr->dtreeQ_front->next;
		agg_recptr->dtreeQ_front->prev = NULL;
	}
	return (dQd_rc);
}
