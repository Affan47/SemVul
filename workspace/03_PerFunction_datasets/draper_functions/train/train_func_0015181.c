nes_manage_apbvt(struct nes_vnic *nesvnic, u32 accel_local_port,
		u32 nic_index, u32 add_port)
{
	struct nes_device *nesdev = nesvnic->nesdev;
	struct nes_hw_cqp_wqe *cqp_wqe;
	struct nes_cqp_request *cqp_request;
	int ret = 0;
	u16 major_code;


	cqp_request = nes_get_cqp_request(nesdev);
	if (cqp_request == NULL) {
		nes_debug(NES_DBG_QP, "Failed to get a cqp_request.\n");
		return -ENOMEM;
	}
	cqp_request->waiting = 1;
	cqp_wqe = &cqp_request->cqp_wqe;

	nes_debug(NES_DBG_QP, "%s APBV for local port=%u(0x%04x), nic_index=%u\n",
			(add_port == NES_MANAGE_APBVT_ADD) ? "ADD" : "DEL",
			accel_local_port, accel_local_port, nic_index);

	nes_fill_init_cqp_wqe(cqp_wqe, nesdev);
	set_wqe_32bit_value(cqp_wqe->wqe_words, NES_CQP_WQE_OPCODE_IDX, (NES_CQP_MANAGE_APBVT |
			((add_port == NES_MANAGE_APBVT_ADD) ? NES_CQP_APBVT_ADD : 0)));
	set_wqe_32bit_value(cqp_wqe->wqe_words, NES_CQP_WQE_ID_IDX,
			((nic_index << NES_CQP_APBVT_NIC_SHIFT) | accel_local_port));

	nes_debug(NES_DBG_QP, "Waiting for CQP completion for APBVT.\n");

	atomic_set(&cqp_request->refcount, 2);
	nes_post_cqp_request(nesdev, cqp_request);

	if (add_port == NES_MANAGE_APBVT_ADD)
		ret = wait_event_timeout(cqp_request->waitq, (cqp_request->request_done != 0),
				NES_EVENT_TIMEOUT);
	nes_debug(NES_DBG_QP, "Completed, ret=%u,  CQP Major:Minor codes = 0x%04X:0x%04X\n",
			ret, cqp_request->major_code, cqp_request->minor_code);
	major_code = cqp_request->major_code;

	nes_put_cqp_request(nesdev, cqp_request);

	if (!ret)
		return -ETIME;
	else if (major_code)
		return -EIO;
	else
		return 0;
}
