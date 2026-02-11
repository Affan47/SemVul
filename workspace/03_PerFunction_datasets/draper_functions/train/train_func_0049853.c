attribute_set_check_value (GkmGenericKey *self, CK_ATTRIBUTE *attr)
{
	guchar buffer[20];

	g_assert (GKM_IS_GENERIC_KEY (self));
	g_assert (attr);


	if (!attr->pValue) {
		attr->ulValueLen = 3;
		return CKR_OK;
	}


	gcry_md_hash_buffer (GCRY_MD_SHA1, buffer, self->value, self->n_value);


	return gkm_attribute_set_data (attr, buffer, 3);
}
