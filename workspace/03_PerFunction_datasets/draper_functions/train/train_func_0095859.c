asn1constraint_range_free(asn1cnst_range_t *cr) {
	if(cr) {
		int i;
		if(cr->elements) {
			for(i = 0; i < cr->el_count; i++)
				asn1constraint_range_free(cr->elements[i]);
			free(cr->elements);
		}
		free(cr);
	}
}
