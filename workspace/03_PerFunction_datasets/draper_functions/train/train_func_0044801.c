lpfc_sli4_mq_release(struct lpfc_queue *q)
{

	if (unlikely(!q))
		return 0;


	q->phba->mbox = NULL;
	q->hba_index = ((q->hba_index + 1) % q->entry_count);
	return 1;
}
