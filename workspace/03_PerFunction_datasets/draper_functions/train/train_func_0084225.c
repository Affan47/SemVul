bnx2i_iscsi_map_sg_list(struct bnx2i_cmd *cmd)
{
	int bd_count;

	bd_count  = bnx2i_map_scsi_sg(cmd->conn->hba, cmd);
	if (!bd_count) {
		struct iscsi_bd *bd = cmd->io_tbl.bd_tbl;

		bd[0].buffer_addr_lo = bd[0].buffer_addr_hi = 0;
		bd[0].buffer_length = bd[0].flags = 0;
	}
	cmd->io_tbl.bd_valid = bd_count;
}
