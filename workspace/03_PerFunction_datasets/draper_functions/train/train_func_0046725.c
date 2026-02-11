lpfc_reg_vpi(struct lpfc_vport *vport, LPFC_MBOXQ_t *pmb)
{
	MAILBOX_t *mb = &pmb->u.mb;
	struct lpfc_hba *phba = vport->phba;

	memset(pmb, 0, sizeof (LPFC_MBOXQ_t));


	if ((phba->sli_rev == LPFC_SLI_REV4) &&
		!(vport->fc_flag & FC_VPORT_NEEDS_REG_VPI))
		mb->un.varRegVpi.upd = 1;

	mb->un.varRegVpi.vpi = phba->vpi_ids[vport->vpi];
	mb->un.varRegVpi.sid = vport->fc_myDID;
	if (phba->sli_rev == LPFC_SLI_REV4)
		mb->un.varRegVpi.vfi = phba->sli4_hba.vfi_ids[vport->vfi];
	else
		mb->un.varRegVpi.vfi = vport->vfi + vport->phba->vfi_base;
	memcpy(mb->un.varRegVpi.wwn, &vport->fc_portname,
	       sizeof(struct lpfc_name));
	mb->un.varRegVpi.wwn[0] = cpu_to_le32(mb->un.varRegVpi.wwn[0]);
	mb->un.varRegVpi.wwn[1] = cpu_to_le32(mb->un.varRegVpi.wwn[1]);

	mb->mbxCommand = MBX_REG_VPI;
	mb->mbxOwner = OWN_HOST;
	return;

}
