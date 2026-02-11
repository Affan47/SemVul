qlafx00_multistatus_entry(struct scsi_qla_host *vha,
	struct rsp_que *rsp, void *pkt)
{
	srb_t		*sp;
	struct multi_sts_entry_fx00 *stsmfx;
	struct qla_hw_data *ha = vha->hw;
	uint32_t handle, hindex, handle_count, i;
	uint16_t que;
	struct req_que *req;
	__le32 *handle_ptr;

	stsmfx = (struct multi_sts_entry_fx00 *) pkt;

	handle_count = stsmfx->handle_count;

	if (handle_count > MAX_HANDLE_COUNT) {
		ql_dbg(ql_dbg_io, vha, 0x3035,
		    "Invalid handle count (0x%x).\n", handle_count);
		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		qla2xxx_wake_dpc(vha);
		return;
	}

	handle_ptr =  &stsmfx->handles[0];

	for (i = 0; i < handle_count; i++) {
		hindex = le32_to_cpu(*handle_ptr);
		handle = LSW(hindex);
		que = MSW(hindex);
		req = ha->req_q_map[que];


		if (handle < req->num_outstanding_cmds) {
			osb();
			sp = req->outstanding_cmds[handle];
		} else {
			sp = NULL;
		}

		if (sp == NULL) {
			ql_dbg(ql_dbg_io, vha, 0x3044,
			    "Invalid status handle (0x%x).\n", handle);
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
			qla2xxx_wake_dpc(vha);
			return;
		}
		qla2x00_process_completed_request(vha, req, handle);
		handle_ptr++;
	}
}
