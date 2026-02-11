macaddrstruct_to_string(const ipv6calc_macaddr *macaddrp, char *resultstring, const uint32_t formatoptions) {
	char tempstring[NI_MAXHOST];


	snprintf(tempstring, sizeof(tempstring) - 1, "%02x:%02x:%02x:%02x:%02x:%02x", (unsigned int) macaddrp->addr[0], (unsigned int) macaddrp->addr[1], (unsigned int) macaddrp->addr[2], (unsigned int) macaddrp->addr[3], (unsigned int) macaddrp->addr[4], (unsigned int) macaddrp->addr[5]);

	if ( (formatoptions & FORMATOPTION_machinereadable) != 0 ) {
		snprintf(resultstring, NI_MAXHOST - 1, "MAC=%s", tempstring);
	} else {
		snprintf(resultstring, NI_MAXHOST - 1, "%s", tempstring);
	};

	return(0);
}
