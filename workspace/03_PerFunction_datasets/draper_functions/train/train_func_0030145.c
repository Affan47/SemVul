esas2r_disc_passthru_dev_addr(struct esas2r_adapter *a,
					  struct esas2r_request *rq)
{
	struct esas2r_disc_context *dc =
		(struct esas2r_disc_context *)rq->interrupt_cx;
	bool rslt;
	struct atto_ioctl *hi;
	struct esas2r_sg_context sgc;

	esas2r_trace_enter();

	esas2r_rq_init_request(rq, a);


	sgc.cur_offset = NULL;
	sgc.get_phys_addr = (PGETPHYSADDR)esas2r_disc_get_phys_addr;
	sgc.length = offsetof(struct atto_ioctl, data)
		     + sizeof(struct atto_hba_get_device_address);

	esas2r_sgc_init(&sgc, a, rq, rq->vrq->ioctl.sge);

	esas2r_build_ioctl_req(a, rq, sgc.length, VDA_IOCTL_HBA);

	if (!esas2r_build_sg_list(a, rq, &sgc)) {
		esas2r_rq_destroy_request(rq, a);

		esas2r_trace_exit();

		return false;
	}

	rq->comp_cb = esas2r_disc_passthru_dev_addr_cb;

	rq->interrupt_cx = dc;


	hi = (struct atto_ioctl *)a->disc_buffer;

	memset(a->disc_buffer, 0, ESAS2R_DISC_BUF_LEN);

	hi->version = ATTO_VER_GET_DEV_ADDR0;
	hi->function = ATTO_FUNC_GET_DEV_ADDR;
	hi->flags = HBAF_TUNNEL;

	hi->data.get_dev_addr.target_id = le32_to_cpu(dc->curr_phys_id);
	hi->data.get_dev_addr.addr_type = dc->dev_addr_type;


	rslt = esas2r_disc_start_request(a, rq);

	esas2r_trace_exit();

	return rslt;
}
