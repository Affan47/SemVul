unmap_eapsim_types(RADIUS_PACKET *r)
{
	VALUE_PAIR             *esvp;

	esvp = pairfind(r->vps, ATTRIBUTE_EAP_BASE+PW_EAP_SIM);
	if (esvp == NULL) {
		radlog(L_ERR, "eap: EAP-Sim attribute not found");
		return 0;
	}

	return unmap_eapsim_basictypes(r, esvp->vp_octets, esvp->length);
}
