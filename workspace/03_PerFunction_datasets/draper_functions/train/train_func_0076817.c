lad_sm_append_strip_mining_cmp(StripMiningCMP **head, StripMiningCMP *cmp)
{
    StripMiningCMP *sm_cmp;

    sm_cmp = *head;


    if(lad_sm_append_check_strip_mining_cmp(*head, cmp)) {

	if (sm_cmp == NULL) {
	    *head = cmp;
	} else {
	    while (sm_cmp->next != NULL) {
		sm_cmp = sm_cmp->next;
	    }
	    sm_cmp->next = cmp;
	}
    }
}
