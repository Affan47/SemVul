csio_reg_rnode(struct csio_rnode *rn)
{
	struct csio_lnode *ln		= csio_rnode_to_lnode(rn);
	struct Scsi_Host *shost		= csio_ln_to_shost(ln);
	struct fc_rport_identifiers ids;
	struct fc_rport  *rport;
	struct csio_service_parms *sp;

	ids.node_name	= wwn_to_u64(csio_rn_wwnn(rn));
	ids.port_name	= wwn_to_u64(csio_rn_wwpn(rn));
	ids.port_id	= rn->nport_id;
	ids.roles	= FC_RPORT_ROLE_UNKNOWN;

	if (rn->role & CSIO_RNFR_INITIATOR || rn->role & CSIO_RNFR_TARGET) {
		rport = rn->rport;
		CSIO_ASSERT(rport != NULL);
		goto update_role;
	}

	rn->rport = fc_remote_port_add(shost, 0, &ids);
	if (!rn->rport) {
		csio_ln_err(ln, "Failed to register rport = 0x%x.\n",
					rn->nport_id);
		return;
	}

	ln->num_reg_rnodes++;
	rport = rn->rport;
	spin_lock_irq(shost->host_lock);
	*((struct csio_rnode **)rport->dd_data) = rn;
	spin_unlock_irq(shost->host_lock);

	sp = &rn->rn_sparm;
	rport->maxframe_size = ntohs(sp->csp.sp_bb_data);
	if (ntohs(sp->clsp[2].cp_class) & FC_CPC_VALID)
		rport->supported_classes = FC_COS_CLASS3;
	else
		rport->supported_classes = FC_COS_UNSPECIFIED;
update_role:
	if (rn->role & CSIO_RNFR_INITIATOR)
		ids.roles |= FC_RPORT_ROLE_FCP_INITIATOR;
	if (rn->role & CSIO_RNFR_TARGET)
		ids.roles |= FC_RPORT_ROLE_FCP_TARGET;

	if (ids.roles != FC_RPORT_ROLE_UNKNOWN)
		fc_remote_port_rolechg(rport, ids.roles);

	rn->scsi_id = rport->scsi_target_id;

	csio_ln_dbg(ln, "Remote port x%x role 0x%x registered\n",
		rn->nport_id, ids.roles);
}
