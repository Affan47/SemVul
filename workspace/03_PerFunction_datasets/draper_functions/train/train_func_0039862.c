SEQUENCE_handle_extensions(asn_TYPE_descriptor_t *td, void *sptr,
		asn_per_outp_t *po1, asn_per_outp_t *po2) {
	asn_SEQUENCE_specifics_t *specs
		= (asn_SEQUENCE_specifics_t *)td->specifics;
	int exts_present = 0;
	int exts_count = 0;
	int edx;

	if(specs->ext_before < 0)
		return 0;


	for(edx = specs->ext_after + 1; edx < td->elements_count; edx++) {
		asn_TYPE_member_t *elm = &td->elements[edx];
		void *memb_ptr;
		void **memb_ptr2;
		int present;

		if(!IN_EXTENSION_GROUP(specs, edx)) {
			ASN_DEBUG("%s (@%d) is not extension", elm->type->name, edx);
			continue;
		}


		if(elm->flags & ATF_POINTER) {
			memb_ptr2 = (void **)((char *)sptr + elm->memb_offset);
			present = (*memb_ptr2 != 0);
		} else {
			memb_ptr = (void *)((char *)sptr + elm->memb_offset);
			memb_ptr2 = &memb_ptr;
			present = 1;
		}

		ASN_DEBUG("checking %s (@%d) present => %d",
			elm->type->name, edx, present);
		exts_count++;
		exts_present += present;


		if(po1 && per_put_few_bits(po1, present, 1))
			return -1;

		if(po2 && present && uper_open_type_put(elm->type,
				elm->per_constraints, *memb_ptr2, po2))
			return -1;

	}

	return exts_present ? exts_count : 0;
}
