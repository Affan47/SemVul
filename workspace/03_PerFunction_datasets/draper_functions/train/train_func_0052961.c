uper_get_nslength(asn_per_data_t *pd) {
	ssize_t length;

	ASN_DEBUG("Getting normally small length");

	if(per_get_few_bits(pd, 1) == 0) {
		length = per_get_few_bits(pd, 6) + 1;
		if(length <= 0) return -1;
		ASN_DEBUG("l=%d", (int)length);
		return length;
	} else {
		int repeat;
		length = uper_get_length(pd, -1, &repeat);
		if(length >= 0 && !repeat) return length;
		return -1;
	}
}
