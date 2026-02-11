csio_fcoe_vnp_read_init_mb(struct csio_lnode *ln, struct csio_mb *mbp,
		uint32_t mb_tmo, uint32_t fcfi, uint32_t vnpi,
		void (*cbfn) (struct csio_hw *, struct csio_mb *))
{
	struct fw_fcoe_vnp_cmd *cmdp =
			(struct fw_fcoe_vnp_cmd *)(mbp->mb);

	CSIO_INIT_MBP(mbp, cmdp, mb_tmo, ln, cbfn, 1);
	cmdp->op_to_fcfi = htonl(FW_CMD_OP_V(FW_FCOE_VNP_CMD)	|
				 FW_CMD_REQUEST_F			|
				 FW_CMD_READ_F			|
				 FW_FCOE_VNP_CMD_FCFI(fcfi));
	cmdp->alloc_to_len16 = htonl(FW_CMD_LEN16_V(sizeof(*cmdp) / 16));
	cmdp->gen_wwn_to_vnpi = htonl(FW_FCOE_VNP_CMD_VNPI(vnpi));
}
