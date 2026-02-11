_range_merge_in(asn1cnst_range_t *into, asn1cnst_range_t *cr) {
	asn1cnst_range_t *r;
	int prev_count = into->el_count;
	int i;

	into->not_PER_visible |= cr->not_PER_visible;
	into->extensible |= cr->extensible;


	for(i = -1; i < cr->el_count; i++) {

		if(i == -1) {
			if(cr->el_count) continue;
			r = cr;
		} else {
			r = cr->elements[i];
		}

		if(_range_insert(into, r)) {
			into->el_count = prev_count;
			return -1;
		}
	}

	if(cr->el_count) {
		cr->el_count = 0;
		_range_free(cr);
	} else {

	}

	return 0;
}
