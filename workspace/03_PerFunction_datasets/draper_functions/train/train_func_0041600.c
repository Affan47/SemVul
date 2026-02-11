bnx2fc_rport_event_handler(struct fc_lport *lport,
				struct fc_rport_priv *rdata,
				enum fc_rport_event event)
{
	struct fcoe_port *port = lport_priv(lport);
	struct bnx2fc_interface *interface = port->priv;
	struct bnx2fc_hba *hba = interface->hba;
	struct fc_rport *rport = rdata->rport;
	struct fc_rport_libfc_priv *rp;
	struct bnx2fc_rport *tgt;
	u32 port_id;

	BNX2FC_HBA_DBG(lport, "rport_event_hdlr: event = %d, port_id = 0x%x\n",
		event, rdata->ids.port_id);
	switch (event) {
	case RPORT_EV_READY:
		if (!rport) {
			printk(KERN_ERR PFX "rport is NULL: ERROR!\n");
			break;
		}

		rp = rport->dd_data;
		if (rport->port_id == FC_FID_DIR_SERV) {


			printk(KERN_ERR PFX "%x - rport_event_handler ERROR\n",
				rdata->ids.port_id);
			break;
		}

		if (rdata->spp_type != FC_TYPE_FCP) {
			BNX2FC_HBA_DBG(lport, "not FCP type target."
				   " not offloading\n");
			break;
		}
		if (!(rdata->ids.roles & FC_RPORT_ROLE_FCP_TARGET)) {
			BNX2FC_HBA_DBG(lport, "not FCP_TARGET"
				   " not offloading\n");
			break;
		}


		mutex_lock(&hba->hba_mutex);
		tgt = (struct bnx2fc_rport *)&rp[1];


		if (test_bit(BNX2FC_FLAG_ENABLED, &tgt->flags)) {
			BNX2FC_TGT_DBG(tgt, "already offloaded\n");
			mutex_unlock(&hba->hba_mutex);
			return;
		}


		bnx2fc_offload_session(port, tgt, rdata);

		BNX2FC_TGT_DBG(tgt, "OFFLOAD num_ofld_sess = %d\n",
			hba->num_ofld_sess);

		if (test_bit(BNX2FC_FLAG_ENABLED, &tgt->flags)) {

			BNX2FC_TGT_DBG(tgt, "sess offloaded\n");

			hba->num_ofld_sess++;

			set_bit(BNX2FC_FLAG_SESSION_READY, &tgt->flags);
		} else {


			BNX2FC_TGT_DBG(tgt, "Port is being logged off as "
				   "offloaded flag not set\n");
		}
		mutex_unlock(&hba->hba_mutex);
		break;
	case RPORT_EV_LOGO:
	case RPORT_EV_FAILED:
	case RPORT_EV_STOP:
		port_id = rdata->ids.port_id;
		if (port_id == FC_FID_DIR_SERV)
			break;

		if (!rport) {
			printk(KERN_INFO PFX "%x - rport not created Yet!!\n",
				port_id);
			break;
		}
		rp = rport->dd_data;
		mutex_lock(&hba->hba_mutex);


		tgt = (struct bnx2fc_rport *)&rp[1];

		if (!(test_bit(BNX2FC_FLAG_ENABLED, &tgt->flags))) {
			mutex_unlock(&hba->hba_mutex);
			break;
		}
		clear_bit(BNX2FC_FLAG_SESSION_READY, &tgt->flags);

		bnx2fc_upload_session(port, tgt);
		hba->num_ofld_sess--;
		BNX2FC_TGT_DBG(tgt, "UPLOAD num_ofld_sess = %d\n",
			hba->num_ofld_sess);


		if ((hba->wait_for_link_down) &&
		    (hba->num_ofld_sess == 0)) {
			wake_up_interruptible(&hba->shutdown_wait);
		}
		mutex_unlock(&hba->hba_mutex);

		break;

	case RPORT_EV_NONE:
		break;
	}
}
