bnx2fc_process_els_compl(struct bnx2fc_cmd *els_req,
			      struct fcoe_task_ctx_entry *task, u8 num_rq)
{
	struct bnx2fc_mp_req *mp_req;
	struct fc_frame_header *fc_hdr;
	u64 *hdr;
	u64 *temp_hdr;

	BNX2FC_ELS_DBG("Entered process_els_compl xid = 0x%x"
			"cmd_type = %d\n", els_req->xid, els_req->cmd_type);

	if (test_and_set_bit(BNX2FC_FLAG_ELS_DONE,
			     &els_req->req_flags)) {
		BNX2FC_ELS_DBG("Timer context finished processing this "
			   "els - 0x%x\n", els_req->xid);

		kref_put(&els_req->refcount, bnx2fc_cmd_release);
		return;
	}


	if (cancel_delayed_work(&els_req->timeout_work))
		kref_put(&els_req->refcount,
			 bnx2fc_cmd_release);

	if (els_req->on_active_queue) {
		list_del_init(&els_req->link);
		els_req->on_active_queue = 0;
	}

	mp_req = &(els_req->mp_req);
	fc_hdr = &(mp_req->resp_fc_hdr);

	hdr = (u64 *)fc_hdr;
	temp_hdr = (u64 *)
		&task->rxwr_only.union_ctx.comp_info.mp_rsp.fc_hdr;
	hdr[0] = cpu_to_be64(temp_hdr[0]);
	hdr[1] = cpu_to_be64(temp_hdr[1]);
	hdr[2] = cpu_to_be64(temp_hdr[2]);

	mp_req->resp_len =
		task->rxwr_only.union_ctx.comp_info.mp_rsp.mp_payload_len;


	if ((els_req->cb_func) && (els_req->cb_arg)) {
		els_req->cb_func(els_req->cb_arg);
		els_req->cb_arg = NULL;
	}

	kref_put(&els_req->refcount, bnx2fc_cmd_release);
}
