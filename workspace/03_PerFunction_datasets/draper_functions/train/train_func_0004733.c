uper_open_type_put(asn_TYPE_descriptor_t *td, asn_per_constraints_t *constraints, void *sptr, asn_per_outp_t *po) {
	void *buf;
	void *bptr;
	ssize_t size;
	size_t toGo;

	ASN_DEBUG("Open type put %s ...", td->name);

	size = uper_encode_to_new_buffer(td, constraints, sptr, &buf);
	if(size <= 0) return -1;

	for(bptr = buf, toGo = size; toGo;) {
		ssize_t maySave = uper_put_length(po, toGo);
		ASN_DEBUG("Prepending length %d to %s and allowing to save %d",
			(int)size, td->name, (int)maySave);
		if(maySave < 0) break;
		if(per_put_many_bits(po, bptr, maySave * 8)) break;
		bptr = (char *)bptr + maySave;
		toGo -= maySave;
	}

	FREEMEM(buf);
	if(toGo) return -1;

	ASN_DEBUG("Open type put %s of length %ld + overhead (1byte?)",
		td->name, (long)size);

	return 0;
}
