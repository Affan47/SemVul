trust_get_hash (GkmXdgTrust *self, GChecksumType ctype, CK_ATTRIBUTE_PTR attr)
{
	GNode *cert;
	GBytes *element;
	CK_RV rv;

	cert = egg_asn1x_node (self->pv->asn, "reference", "certComplete", NULL);
	g_return_val_if_fail (cert, CKR_GENERAL_ERROR);


	if (!egg_asn1x_have (cert)) {
		gkm_debug ("CKR_ATTRIBUTE_TYPE_INVALID: %s wants certComplete which is not part of assertion",
		           gkm_log_attr_type (attr->type));
		return CKR_ATTRIBUTE_TYPE_INVALID;
	}

	element = egg_asn1x_get_element_raw (cert);
	g_return_val_if_fail (element != NULL, CKR_GENERAL_ERROR);

	rv = gkm_attribute_set_checksum (attr, ctype,
	                                 g_bytes_get_data (element, NULL),
	                                 g_bytes_get_size (element));

	g_bytes_unref (element);
	return rv;
}
