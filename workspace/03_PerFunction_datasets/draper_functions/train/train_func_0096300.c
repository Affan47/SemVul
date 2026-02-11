read_attribute(GkmObject *object, CK_ATTRIBUTE_TYPE type, CK_ATTRIBUTE_PTR *result)
{
	CK_ATTRIBUTE attr;
	CK_RV rv;

	g_assert (GKM_IS_OBJECT (object));
	g_assert (result);

	*result = NULL;

	attr.type = type;
	attr.pValue = NULL;
	attr.ulValueLen = 0;


	rv = gkm_object_get_attribute (object, NULL, &attr);


	if (rv == CKR_ATTRIBUTE_TYPE_INVALID) {
		*result = NULL;
		return TRUE;
	}

	if (rv != CKR_OK) {
		g_warning ("accessing indexed attribute failed");
		return FALSE;
	}


	if (attr.ulValueLen) {
		attr.pValue = g_malloc0 (attr.ulValueLen);
		rv = gkm_object_get_attribute (object, NULL, &attr);
		if (rv != CKR_OK) {
			g_warning ("accessing indexed attribute failed");
			g_free (attr.pValue);
			return FALSE;
		}
	}

	*result = g_slice_new (CK_ATTRIBUTE);
	memcpy (*result, &attr, sizeof (CK_ATTRIBUTE));
	return TRUE;
}
