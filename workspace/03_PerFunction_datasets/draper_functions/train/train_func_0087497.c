lpfc_free_iocb_list(struct lpfc_hba *phba)
{
	struct lpfc_iocbq *iocbq_entry = NULL, *iocbq_next = NULL;

	spin_lock_irq(&phba->hbalock);
	list_for_each_entry_safe(iocbq_entry, iocbq_next,
				 &phba->lpfc_iocb_list, list) {
		list_del(&iocbq_entry->list);
		kfree(iocbq_entry);
		phba->total_iocbq_bufs--;
	}
	spin_unlock_irq(&phba->hbalock);

	return;
}
