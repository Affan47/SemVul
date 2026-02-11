brcmf_fws_macdesc_deinit(struct brcmf_fws_mac_descriptor *desc)
{
	brcmf_dbg(TRACE,
		  "enter: ea=%pM, ifidx=%u\n", desc->ea, desc->interface_id);
	desc->occupied = 0;
	desc->state = BRCMF_FWS_STATE_CLOSE;
	desc->requested_credit = 0;
	desc->requested_packet = 0;
}
