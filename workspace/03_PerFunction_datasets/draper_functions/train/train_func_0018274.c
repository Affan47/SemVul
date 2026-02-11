lpfc_get_host_fabric_name (struct Scsi_Host *shost)
{
	struct lpfc_vport *vport = (struct lpfc_vport *) shost->hostdata;
	struct lpfc_hba   *phba = vport->phba;
	u64 node_name;

	spin_lock_irq(shost->host_lock);

	if ((vport->port_state > LPFC_FLOGI) &&
	    ((vport->fc_flag & FC_FABRIC) ||
	     ((phba->fc_topology == LPFC_TOPOLOGY_LOOP) &&
	      (vport->fc_flag & FC_PUBLIC_LOOP))))
		node_name = wwn_to_u64(phba->fc_fabparam.nodeName.u.wwn);
	else

		node_name = 0;

	spin_unlock_irq(shost->host_lock);

	fc_host_fabric_name(shost) = node_name;
}
