bnx2fc_post_io_req(struct bnx2fc_rport *tgt,
			       struct bnx2fc_cmd *io_req)
{
	struct fcoe_task_ctx_entry *task;
	struct fcoe_task_ctx_entry *task_page;
	struct scsi_cmnd *sc_cmd = io_req->sc_cmd;
	struct fcoe_port *port = tgt->port;
	struct bnx2fc_interface *interface = port->priv;
	struct bnx2fc_hba *hba = interface->hba;
	struct fc_lport *lport = port->lport;
	struct fc_stats *stats;
	int task_idx, index;
	u16 xid;


	io_req->cmd_type = BNX2FC_SCSI_CMD;
	io_req->port = port;
	io_req->tgt = tgt;
	io_req->data_xfer_len = scsi_bufflen(sc_cmd);
	sc_cmd->SCp.ptr = (char *)io_req;

	stats = per_cpu_ptr(lport->stats, get_cpu());
	if (sc_cmd->sc_data_direction == DMA_FROM_DEVICE) {
		io_req->io_req_flags = BNX2FC_READ;
		stats->InputRequests++;
		stats->InputBytes += io_req->data_xfer_len;
	} else if (sc_cmd->sc_data_direction == DMA_TO_DEVICE) {
		io_req->io_req_flags = BNX2FC_WRITE;
		stats->OutputRequests++;
		stats->OutputBytes += io_req->data_xfer_len;
	} else {
		io_req->io_req_flags = 0;
		stats->ControlRequests++;
	}
	put_cpu();

	xid = io_req->xid;


	if (bnx2fc_build_bd_list_from_sg(io_req)) {
		printk(KERN_ERR PFX "BD list creation failed\n");
		kref_put(&io_req->refcount, bnx2fc_cmd_release);
		return -EAGAIN;
	}

	task_idx = xid / BNX2FC_TASKS_PER_PAGE;
	index = xid % BNX2FC_TASKS_PER_PAGE;


	task_page = (struct fcoe_task_ctx_entry *) hba->task_ctx[task_idx];
	task = &(task_page[index]);
	bnx2fc_init_task(io_req, task);

	if (tgt->flush_in_prog) {
		printk(KERN_ERR PFX "Flush in progress..Host Busy\n");
		kref_put(&io_req->refcount, bnx2fc_cmd_release);
		return -EAGAIN;
	}

	if (!test_bit(BNX2FC_FLAG_SESSION_READY, &tgt->flags)) {
		printk(KERN_ERR PFX "Session not ready...post_io\n");
		kref_put(&io_req->refcount, bnx2fc_cmd_release);
		return -EAGAIN;
	}


	if (tgt->io_timeout)
		bnx2fc_cmd_timer_set(io_req, BNX2FC_IO_TIMEOUT);

	bnx2fc_add_2_sq(tgt, xid);


	io_req->on_active_queue = 1;

	list_add_tail(&io_req->link, &tgt->active_cmd_queue);


	bnx2fc_ring_doorbell(tgt);
	return 0;
}
