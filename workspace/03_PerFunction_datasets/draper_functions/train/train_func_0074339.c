lpfc_more_adisc(struct lpfc_vport *vport)
{
	if (vport->num_disc_nodes)
		vport->num_disc_nodes--;

	lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
			 "0210 Continue discovery with %d ADISCs to go "
			 "Data: x%x x%x x%x\n",
			 vport->num_disc_nodes, vport->fc_adisc_cnt,
			 vport->fc_flag, vport->port_state);

	if (vport->fc_flag & FC_NLP_MORE) {
		lpfc_set_disctmo(vport);

		lpfc_els_disc_adisc(vport);
	}
	if (!vport->num_disc_nodes)
		lpfc_adisc_done(vport);
	return;
}
