lpfc_bsg_mbox_ext_session_reset(struct lpfc_hba *phba)
{
	if (phba->mbox_ext_buf_ctx.state == LPFC_BSG_MBOX_IDLE)
		return;


	lpfc_bsg_dma_page_list_free(phba,
				    &phba->mbox_ext_buf_ctx.ext_dmabuf_list);
	lpfc_bsg_dma_page_free(phba, phba->mbox_ext_buf_ctx.mbx_dmabuf);

	memset((char *)&phba->mbox_ext_buf_ctx, 0,
	       sizeof(struct lpfc_mbox_ext_buf_ctx));
	INIT_LIST_HEAD(&phba->mbox_ext_buf_ctx.ext_dmabuf_list);

	return;
}
