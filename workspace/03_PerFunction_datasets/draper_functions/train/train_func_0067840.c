bfa_sfp_scn_aen_post(struct bfa_sfp_s *sfp, struct bfi_sfp_scn_s *rsp)
{
	struct bfad_s *bfad = (struct bfad_s *)sfp->ioc->bfa->bfad;
	struct bfa_aen_entry_s  *aen_entry;
	enum bfa_port_aen_event aen_evt = 0;

	bfa_trc(sfp, (((u64)rsp->pomlvl) << 16) | (((u64)rsp->sfpid) << 8) |
		      ((u64)rsp->event));

	bfad_get_aen_entry(bfad, aen_entry);
	if (!aen_entry)
		return;

	aen_entry->aen_data.port.ioc_type = bfa_ioc_get_type(sfp->ioc);
	aen_entry->aen_data.port.pwwn = sfp->ioc->attr->pwwn;
	aen_entry->aen_data.port.mac = bfa_ioc_get_mac(sfp->ioc);

	switch (rsp->event) {
	case BFA_SFP_SCN_INSERTED:
		aen_evt = BFA_PORT_AEN_SFP_INSERT;
		break;
	case BFA_SFP_SCN_REMOVED:
		aen_evt = BFA_PORT_AEN_SFP_REMOVE;
		break;
	case BFA_SFP_SCN_FAILED:
		aen_evt = BFA_PORT_AEN_SFP_ACCESS_ERROR;
		break;
	case BFA_SFP_SCN_UNSUPPORT:
		aen_evt = BFA_PORT_AEN_SFP_UNSUPPORT;
		break;
	case BFA_SFP_SCN_POM:
		aen_evt = BFA_PORT_AEN_SFP_POM;
		aen_entry->aen_data.port.level = rsp->pomlvl;
		break;
	default:
		bfa_trc(sfp, rsp->event);
		WARN_ON(1);
	}


	bfad_im_post_vendor_event(aen_entry, bfad, ++sfp->ioc->ioc_aen_seq,
				  BFA_AEN_CAT_PORT, aen_evt);
}
