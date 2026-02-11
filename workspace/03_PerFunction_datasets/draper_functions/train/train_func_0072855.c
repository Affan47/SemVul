ldns_rr_class2buffer_str(ldns_buffer *output,
                         const ldns_rr_class klass)
{
	ldns_lookup_table *lt;

	lt = ldns_lookup_by_id(ldns_rr_classes, klass);
	if (lt) {
		ldns_buffer_printf(output, "%s", lt->name);
	} else {
		ldns_buffer_printf(output, "CLASS%d", klass);
	}
	return ldns_buffer_status(output);
}
