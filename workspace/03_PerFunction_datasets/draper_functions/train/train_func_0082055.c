bnx2fc_elstm_alloc(struct bnx2fc_rport *tgt, int type)
{
	struct fcoe_port *port = tgt->port;
	struct bnx2fc_interface *interface = port->priv;
	struct bnx2fc_cmd_mgr *cmd_mgr = interface->hba->cmd_mgr;
	struct bnx2fc_cmd *io_req;
	struct list_head *listp;
	struct io_bdt *bd_tbl;
	int index = RESERVE_FREE_LIST_INDEX;
	u32 free_sqes;
	u32 max_sqes;
	u16 xid;

	max_sqes = tgt->max_sqes;
	switch (type) {
	case BNX2FC_TASK_MGMT_CMD:
		max_sqes = BNX2FC_TM_MAX_SQES;
		break;
	case BNX2FC_ELS:
		max_sqes = BNX2FC_ELS_MAX_SQES;
		break;
	default:
		break;
	}


	spin_lock_bh(&cmd_mgr->free_list_lock[index]);
	free_sqes = atomic_read(&tgt->free_sqes);
	if ((list_empty(&(cmd_mgr->free_list[index]))) ||
	    (tgt->num_active_ios.counter  >= max_sqes) ||
	    (free_sqes + max_sqes <= BNX2FC_SQ_WQES_MAX)) {
		BNX2FC_TGT_DBG(tgt, "No free els_tm cmds available "
			"ios(%d):sqes(%d)\n",
			tgt->num_active_ios.counter, tgt->max_sqes);
		if (list_empty(&(cmd_mgr->free_list[index])))
			printk(KERN_ERR PFX "elstm_alloc: list_empty\n");
		spin_unlock_bh(&cmd_mgr->free_list_lock[index]);
		return NULL;
	}

	listp = (struct list_head *)
			cmd_mgr->free_list[index].next;
	list_del_init(listp);
	io_req = (struct bnx2fc_cmd *) listp;
	xid = io_req->xid;
	cmd_mgr->cmds[xid] = io_req;
	atomic_inc(&tgt->num_active_ios);
	atomic_dec(&tgt->free_sqes);
	spin_unlock_bh(&cmd_mgr->free_list_lock[index]);

	INIT_LIST_HEAD(&io_req->link);

	io_req->port = port;
	io_req->cmd_mgr = cmd_mgr;
	io_req->req_flags = 0;
	io_req->cmd_type = type;


	bd_tbl = io_req->bd_tbl = cmd_mgr->io_bdt_pool[xid];
	bd_tbl->io_req = io_req;


	kref_init(&io_req->refcount);
	return io_req;
}
