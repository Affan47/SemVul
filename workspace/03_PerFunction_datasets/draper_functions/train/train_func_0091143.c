lpfc_sli4_wq_release(struct lpfc_queue *q, uint32_t index)
{
	uint32_t released = 0;


	if (unlikely(!q))
		return 0;

	if (q->hba_index == index)
		return 0;
	do {
		q->hba_index = ((q->hba_index + 1) % q->entry_count);
		released++;
	} while (q->hba_index != index);
	return released;
}
