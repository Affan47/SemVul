lpfc_sli4_wq_put(struct lpfc_queue *q, union lpfc_wqe *wqe)
{
	union lpfc_wqe *temp_wqe;
	struct lpfc_register doorbell;
	uint32_t host_index;
	uint32_t idx;


	if (unlikely(!q))
		return -ENOMEM;
	temp_wqe = q->qe[q->host_index].wqe;


	idx = ((q->host_index + 1) % q->entry_count);
	if (idx == q->hba_index) {
		q->WQ_overflow++;
		return -ENOMEM;
	}
	q->WQ_posted++;

	if (!((q->host_index + 1) % q->entry_repost))
		bf_set(wqe_wqec, &wqe->generic.wqe_com, 1);
	if (q->phba->sli3_options & LPFC_SLI4_PHWQ_ENABLED)
		bf_set(wqe_wqid, &wqe->generic.wqe_com, q->queue_id);
	lpfc_sli_pcimem_bcopy(wqe, temp_wqe, q->entry_size);

	wmb();


	host_index = q->host_index;

	q->host_index = idx;


	doorbell.word0 = 0;
	if (q->db_format == LPFC_DB_LIST_FORMAT) {
		bf_set(lpfc_wq_db_list_fm_num_posted, &doorbell, 1);
		bf_set(lpfc_wq_db_list_fm_index, &doorbell, host_index);
		bf_set(lpfc_wq_db_list_fm_id, &doorbell, q->queue_id);
	} else if (q->db_format == LPFC_DB_RING_FORMAT) {
		bf_set(lpfc_wq_db_ring_fm_num_posted, &doorbell, 1);
		bf_set(lpfc_wq_db_ring_fm_id, &doorbell, q->queue_id);
	} else {
		return -EINVAL;
	}
	writel(doorbell.word0, q->db_regaddr);

	return 0;
}
