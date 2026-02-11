cnic_l2_completion(struct cnic_local *cp)
{
	u16 hw_cons, sw_cons;
	struct cnic_uio_dev *udev = cp->udev;
	union eth_rx_cqe *cqe, *cqe_ring = (union eth_rx_cqe *)
					(udev->l2_ring + (2 * CNIC_PAGE_SIZE));
	u32 cmd;
	int comp = 0;

	if (!test_bit(CNIC_F_BNX2X_CLASS, &cp->dev->flags))
		return 0;

	hw_cons = *cp->rx_cons_ptr;
	if ((hw_cons & BNX2X_MAX_RCQ_DESC_CNT) == BNX2X_MAX_RCQ_DESC_CNT)
		hw_cons++;

	sw_cons = cp->rx_cons;
	while (sw_cons != hw_cons) {
		u8 cqe_fp_flags;

		cqe = &cqe_ring[sw_cons & BNX2X_MAX_RCQ_DESC_CNT];
		cqe_fp_flags = cqe->fast_path_cqe.type_error_flags;
		if (cqe_fp_flags & ETH_FAST_PATH_RX_CQE_TYPE) {
			cmd = le32_to_cpu(cqe->ramrod_cqe.conn_and_cmd_data);
			cmd >>= COMMON_RAMROD_ETH_RX_CQE_CMD_ID_SHIFT;
			if (cmd == RAMROD_CMD_ID_ETH_CLIENT_SETUP ||
			    cmd == RAMROD_CMD_ID_ETH_HALT)
				comp++;
		}
		sw_cons = BNX2X_NEXT_RCQE(sw_cons);
	}
	return comp;
}
