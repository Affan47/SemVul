asn1p_value_fromref(asn1p_ref_t *ref, int do_copy) {
	if(ref) {
		asn1p_value_t *v = calloc(1, sizeof *v);
		if(v) {
			if(do_copy) {
				v->value.reference = asn1p_ref_clone(ref);
				if(v->value.reference == NULL) {
					free(v);
					return NULL;
				}
			} else {
				v->value.reference = ref;
			}
			v->type = ATV_REFERENCED;
		}
		return v;
	} else {
		errno = EINVAL;
		return NULL;
	}
}
