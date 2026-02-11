ANY_to_type(ANY_t *st, asn_TYPE_descriptor_t *td, void **struct_ptr) {
	asn_dec_rval_t rval;
	void *newst = 0;

	if(!st || !td || !struct_ptr) {
		errno = EINVAL;
		return -1;
	}

	if(st->buf == 0) {

		*struct_ptr = (void *)0;
		return 0;
	}

	rval = ber_decode(0, td, (void **)&newst, st->buf, st->size);
	if(rval.code == RC_OK) {
		*struct_ptr = newst;
		return 0;
	} else {

		ASN_STRUCT_FREE(*td, newst);
		return -1;
	}
}
