mv_handle_dev_err(struct ata_port *ap, u32 edma_err_cause)
{
	struct mv_port_priv *pp = ap->private_data;

	if (!(pp->pp_flags & MV_PP_FLAG_EDMA_EN))
		return 0;
	if (!(pp->pp_flags & MV_PP_FLAG_FBS_EN))
		return 0;

	if (!(edma_err_cause & EDMA_ERR_DEV))
		return 0;
	edma_err_cause &= ~EDMA_ERR_IRQ_TRANSIENT;
	if (edma_err_cause & ~(EDMA_ERR_DEV | EDMA_ERR_SELF_DIS))
		return 0;

	if (pp->pp_flags & MV_PP_FLAG_NCQ_EN) {


		if (edma_err_cause & EDMA_ERR_SELF_DIS) {
			ata_port_warn(ap, "%s: err_cause=0x%x pp_flags=0x%x\n",
				      __func__, edma_err_cause, pp->pp_flags);
			return 0;
		}
		return mv_handle_fbs_ncq_dev_err(ap);
	} else {


		if (!(edma_err_cause & EDMA_ERR_SELF_DIS)) {
			ata_port_warn(ap, "%s: err_cause=0x%x pp_flags=0x%x\n",
				      __func__, edma_err_cause, pp->pp_flags);
			return 0;
		}
		return mv_handle_fbs_non_ncq_dev_err(ap);
	}
	return 0;
}
