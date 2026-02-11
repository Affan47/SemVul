bfa_fcs_lport_aen_post(struct bfa_fcs_lport_s *port,
			enum bfa_lport_aen_event event)
{
	struct bfad_s *bfad = (struct bfad_s *)port->fabric->fcs->bfad;
	struct bfa_aen_entry_s  *aen_entry;

	bfad_get_aen_entry(bfad, aen_entry);
	if (!aen_entry)
		return;

	aen_entry->aen_data.lport.vf_id = port->fabric->vf_id;
	aen_entry->aen_data.lport.roles = port->port_cfg.roles;
	aen_entry->aen_data.lport.ppwwn = bfa_fcs_lport_get_pwwn(
					bfa_fcs_get_base_port(port->fcs));
	aen_entry->aen_data.lport.lpwwn = bfa_fcs_lport_get_pwwn(port);


	bfad_im_post_vendor_event(aen_entry, bfad, ++port->fcs->fcs_aen_seq,
				  BFA_AEN_CAT_LPORT, event);
}
