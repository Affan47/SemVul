bnx2fc_send_srr(struct bnx2fc_cmd *orig_io_req, u32 offset, u8 r_ctl)
{
	struct fcp_srr srr;
	struct bnx2fc_rport *tgt = orig_io_req->tgt;
	struct fc_lport *lport = tgt->rdata->local_port;
	struct bnx2fc_els_cb_arg *cb_arg = NULL;
	u32 r_a_tov = lport->r_a_tov;
	int rc;

	BNX2FC_IO_DBG(orig_io_req, "Sending SRR\n");
	memset(&srr, 0, sizeof(srr));

	cb_arg = kzalloc(sizeof(struct bnx2fc_els_cb_arg), GFP_ATOMIC);
	if (!cb_arg) {
		printk(KERN_ERR PFX "Unable to allocate cb_arg for SRR\n");
		rc = -ENOMEM;
		goto srr_err;
	}
	kref_get(&orig_io_req->refcount);

	cb_arg->aborted_io_req = orig_io_req;

	srr.srr_op = ELS_SRR;
	srr.srr_ox_id = htons(orig_io_req->xid);
	srr.srr_rx_id = htons(orig_io_req->task->rxwr_txrd.var_ctx.rx_id);
	srr.srr_rel_off = htonl(offset);
	srr.srr_r_ctl = r_ctl;
	orig_io_req->srr_offset = offset;
	orig_io_req->srr_rctl = r_ctl;

	rc = bnx2fc_initiate_els(tgt, ELS_SRR, &srr, sizeof(srr),
				 bnx2fc_srr_compl, cb_arg,
				 r_a_tov);
srr_err:
	if (rc) {
		BNX2FC_IO_DBG(orig_io_req, "SRR failed - release\n");
		spin_lock_bh(&tgt->tgt_lock);
		kref_put(&orig_io_req->refcount, bnx2fc_cmd_release);
		spin_unlock_bh(&tgt->tgt_lock);
		kfree(cb_arg);
	} else
		set_bit(BNX2FC_FLAG_SRR_SENT, &orig_io_req->req_flags);

	return rc;
}
