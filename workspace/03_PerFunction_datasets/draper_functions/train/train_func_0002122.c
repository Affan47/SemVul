ali_check_atapi_dma(struct ata_queued_cmd *qc)
{
	if (!ali_atapi_dma) {


		return -EOPNOTSUPP;
	}


	if (atapi_cmd_type(qc->cdb[0]) == ATAPI_MISC)
		return -EOPNOTSUPP;
	return 0;
}
