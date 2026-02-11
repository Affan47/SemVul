lpfc_free_bsg_buffers(struct lpfc_hba *phba, struct lpfc_dmabuf *mlist)
{
	struct lpfc_dmabuf *mlast, *next_mlast;

	if (mlist) {
		list_for_each_entry_safe(mlast, next_mlast, &mlist->list,
					 list) {
			lpfc_mbuf_free(phba, mlast->virt, mlast->phys);
			list_del(&mlast->list);
			kfree(mlast);
		}
		lpfc_mbuf_free(phba, mlist->virt, mlist->phys);
		kfree(mlist);
	}
	return;
}
