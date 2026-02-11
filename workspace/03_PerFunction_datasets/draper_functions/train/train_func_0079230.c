qla8044_check_dma_engine_state(struct scsi_qla_host *vha)
{
	struct qla_hw_data *ha = vha->hw;
	int rval = QLA_SUCCESS;
	uint32_t dma_eng_num = 0, cmd_sts_and_cntrl = 0;
	uint64_t dma_base_addr = 0;
	struct qla8044_minidump_template_hdr *tmplt_hdr = NULL;

	tmplt_hdr = ha->md_tmplt_hdr;
	dma_eng_num =
	    tmplt_hdr->saved_state_array[ISP8044_PEX_DMA_ENGINE_INDEX];
	dma_base_addr = ISP8044_PEX_DMA_BASE_ADDRESS +
		(dma_eng_num * ISP8044_PEX_DMA_NUM_OFFSET);


	rval = qla8044_rd_reg_indirect(vha,
	    (dma_base_addr + ISP8044_PEX_DMA_CMD_STS_AND_CNTRL),
	    &cmd_sts_and_cntrl);
	if (rval)
		return QLA_FUNCTION_FAILED;


	if (cmd_sts_and_cntrl & BIT_31)
		return QLA_SUCCESS;

	return QLA_FUNCTION_FAILED;
}
