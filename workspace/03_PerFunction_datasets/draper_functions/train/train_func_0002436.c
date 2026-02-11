lpfc_debug_save_data(struct lpfc_hba *phba, struct scsi_cmnd *cmnd)
{
	void *src, *dst;
	struct scatterlist *sgde = scsi_sglist(cmnd);

	if (!_dump_buf_data) {
		lpfc_printf_log(phba, KERN_ERR, LOG_BG,
			"9050 BLKGRD: ERROR %s _dump_buf_data is NULL\n",
				__func__);
		return;
	}


	if (!sgde) {
		lpfc_printf_log(phba, KERN_ERR, LOG_BG,
			"9051 BLKGRD: ERROR: data scatterlist is null\n");
		return;
	}

	dst = (void *) _dump_buf_data;
	while (sgde) {
		src = sg_virt(sgde);
		memcpy(dst, src, sgde->length);
		dst += sgde->length;
		sgde = sg_next(sgde);
	}
}
