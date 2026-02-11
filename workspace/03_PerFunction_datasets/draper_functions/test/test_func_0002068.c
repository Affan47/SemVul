asn1print_ref(asn1p_ref_t *ref, enum asn1print_flags flags) {
	int cc;

	(void)flags;

	for(cc = 0; cc < ref->comp_count; cc++) {
		if(cc) printf(".");
		printf("%s", ref->components[cc].name);
	}

	return 0;
}
