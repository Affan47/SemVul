dns_zone_loadandthaw(dns_zone_t *zone) {
	isc_result_t result;

	if (inline_raw(zone))
		result = zone_load(zone->secure, DNS_ZONELOADFLAG_THAW);
	else
		result = zone_load(zone, DNS_ZONELOADFLAG_THAW);

	switch (result) {
	case DNS_R_CONTINUE:

		break;
	case DNS_R_UPTODATE:
	case ISC_R_SUCCESS:
	case DNS_R_SEENINCLUDE:
		zone->update_disabled = ISC_FALSE;
		break;
	case DNS_R_NOMASTERFILE:
		zone->update_disabled = ISC_FALSE;
		break;
	default:

		break;
	}
	return (result);
}
