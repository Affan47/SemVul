vmsg_init_weight(void)
{
	size_t i;

	pt_weight = patricia_create(VMSG_TYPE_BITLEN);

	for (i = 0; i < G_N_ELEMENTS(vmsg_weight_map); i++) {
		const struct vmsg_weight *vw = &vmsg_weight_map[i];
		gnutella_vendor_t *key = walloc(VMSG_TYPE_LEN);

		gnutella_vendor_set_code(key, vw->vendor);
		gnutella_vendor_set_selector_id(key, vw->id);

		patricia_insert(pt_weight, key, uint_to_pointer(vw->weight));
	}
}
