lpfc_sli4_set_rsp_sgl_last(struct lpfc_hba *phba,
				struct lpfc_scsi_buf *lpfc_cmd)
{
	struct sli4_sge *sgl = (struct sli4_sge *)lpfc_cmd->fcp_bpl;
	if (sgl) {
		sgl += 1;
		sgl->word2 = le32_to_cpu(sgl->word2);
		bf_set(lpfc_sli4_sge_last, sgl, 1);
		sgl->word2 = cpu_to_le32(sgl->word2);
	}
}
