knot_response_add_rrset_additional(knot_packet_t *response,
                                       knot_rrset_t *rrset, uint32_t flags)
{
	if (response == NULL || rrset == NULL) {
		return KNOT_EINVAL;
	}

	int ret;


	if (knot_wire_get_arcount(response->wireformat) == 0
	    && response->opt_rr.version != EDNS_NOT_SUPPORTED
	    && (ret = knot_packet_edns_to_wire(response)) != KNOT_EOK) {
		return ret;
	}

	if (response->ar_rrsets == response->max_ar_rrsets
	    && knot_packet_realloc_rrsets(&response->additional,
			&response->max_ar_rrsets, &response->mm)
		!= 0) {
		return KNOT_ENOMEM;
	}

	if ((flags & KNOT_PF_CHECKDUP) && knot_packet_contains(response, rrset,
	                                            KNOT_RRSET_COMPARE_PTR)) {
		return KNOT_EOK;
	}

	dbg_response_verb("Trying to add RRSet to Additional section.\n");

	int rrs = knot_response_try_add_rrset(response->additional,
	                                        &response->ar_rrsets, response,
	                                        response->max_size
	                                        - response->size
	                                        - response->tsig_size, rrset,
	                                        flags);

	if (rrs >= 0) {
		knot_wire_add_arcount(response->wireformat, rrs);
		return KNOT_EOK;
	}

	return KNOT_ESPACE;
}
