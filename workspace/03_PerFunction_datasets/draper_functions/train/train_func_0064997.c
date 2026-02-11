print_section(dns_message_t *message, int section, isc_buffer_t *buf) {
	isc_result_t result;
	isc_region_t r;

	result = dns_message_sectiontotext(message, section,
					   &dns_master_style_full, 0, buf);
	if (result != ISC_R_SUCCESS)
		goto fail;

	isc_buffer_usedregion(buf, &r);
	printf("%.*s", (int)r.length, (char *)r.base);

	return;

 fail:
	fprintf(stderr, "failed to convert a section\n");
}
