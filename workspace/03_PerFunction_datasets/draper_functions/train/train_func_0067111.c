bfa_ioc_aen_post(struct bfa_ioc_s *ioc, enum bfa_ioc_aen_event event)
{
	struct bfad_s *bfad = (struct bfad_s *)ioc->bfa->bfad;
	struct bfa_aen_entry_s	*aen_entry;
	enum bfa_ioc_type_e ioc_type;

	bfad_get_aen_entry(bfad, aen_entry);
	if (!aen_entry)
		return;

	ioc_type = bfa_ioc_get_type(ioc);
	switch (ioc_type) {
	case BFA_IOC_TYPE_FC:
		aen_entry->aen_data.ioc.pwwn = ioc->attr->pwwn;
		break;
	case BFA_IOC_TYPE_FCoE:
		aen_entry->aen_data.ioc.pwwn = ioc->attr->pwwn;
		aen_entry->aen_data.ioc.mac = bfa_ioc_get_mac(ioc);
		break;
	case BFA_IOC_TYPE_LL:
		aen_entry->aen_data.ioc.mac = bfa_ioc_get_mac(ioc);
		break;
	default:
		WARN_ON(ioc_type != BFA_IOC_TYPE_FC);
		break;
	}


	aen_entry->aen_data.ioc.ioc_type = ioc_type;
	bfad_im_post_vendor_event(aen_entry, bfad, ++ioc->ioc_aen_seq,
				  BFA_AEN_CAT_IOC, event);
}
