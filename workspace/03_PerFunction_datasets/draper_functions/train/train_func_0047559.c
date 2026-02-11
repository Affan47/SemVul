parse_pkcs12_bag_friendly_name (GNode *asn)
{
	guint count, i;
	GQuark oid;
	GNode *node;
	GNode *asn_str;
	gchar *result;

	if (asn == NULL)
		return NULL;

	count = egg_asn1x_count (asn);
	for (i = 1; i <= count; i++) {
		oid = egg_asn1x_get_oid_as_quark (egg_asn1x_node (asn, i, "type", NULL));
		if (oid == GCR_OID_PKCS9_ATTRIBUTE_FRIENDLY) {
			node = egg_asn1x_node (asn, i, "values", 1, NULL);
			if (node != NULL) {
				asn_str = egg_asn1x_get_any_as (node, pkix_asn1_tab, "BMPString");
				if (asn_str) {
					result = egg_asn1x_get_bmpstring_as_utf8 (asn_str);
					egg_asn1x_destroy (asn_str);
					return result;
				}
			}
		}
	}

	return NULL;
}
