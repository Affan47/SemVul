bnx2x_free_fw_stats_mem(struct bnx2x *bp)
{
	BNX2X_PCI_FREE(bp->fw_stats, bp->fw_stats_mapping,
		       bp->fw_stats_data_sz + bp->fw_stats_req_sz);
	return;
}
