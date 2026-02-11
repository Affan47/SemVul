nv_adma_check_cpb(struct ata_port *ap, int cpb_num, int force_err)
{
	struct nv_adma_port_priv *pp = ap->private_data;
	u8 flags = pp->cpb[cpb_num].resp_flags;

	VPRINTK("CPB %d, flags=0x%x\n", cpb_num, flags);

	if (unlikely((force_err ||
		     flags & (NV_CPB_RESP_ATA_ERR |
			      NV_CPB_RESP_CMD_ERR |
			      NV_CPB_RESP_CPB_ERR)))) {
		struct ata_eh_info *ehi = &ap->link.eh_info;
		int freeze = 0;

		ata_ehi_clear_desc(ehi);
		__ata_ehi_push_desc(ehi, "CPB resp_flags 0x%x: ", flags);
		if (flags & NV_CPB_RESP_ATA_ERR) {
			ata_ehi_push_desc(ehi, "ATA error");
			ehi->err_mask |= AC_ERR_DEV;
		} else if (flags & NV_CPB_RESP_CMD_ERR) {
			ata_ehi_push_desc(ehi, "CMD error");
			ehi->err_mask |= AC_ERR_DEV;
		} else if (flags & NV_CPB_RESP_CPB_ERR) {
			ata_ehi_push_desc(ehi, "CPB error");
			ehi->err_mask |= AC_ERR_SYSTEM;
			freeze = 1;
		} else {

			ata_ehi_push_desc(ehi, "unknown");
			ehi->err_mask |= AC_ERR_OTHER;
			freeze = 1;
		}

		if (freeze)
			ata_port_freeze(ap);
		else
			ata_port_abort(ap);
		return -1;
	}

	if (likely(flags & NV_CPB_RESP_DONE))
		return 1;
	return 0;
}
