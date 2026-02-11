gkm_session_C_GetAttributeValue (GkmSession* self, CK_OBJECT_HANDLE handle,
                                 CK_ATTRIBUTE_PTR template, CK_ULONG count)
{
	GkmObject *object;
	CK_ULONG i;
	CK_RV code, rv;

	g_return_val_if_fail (GKM_IS_SESSION (self), CKR_SESSION_HANDLE_INVALID);
	if (!(!count || template))
		return CKR_ARGUMENTS_BAD;

	rv = gkm_session_lookup_readable_object (self, handle, &object);
	if (rv != CKR_OK)
		return rv;

	rv = CKR_OK;

	for (i = 0; i < count; ++i) {
		code = gkm_object_get_attribute (object, self, &template[i]);


		if (code == CKR_ATTRIBUTE_SENSITIVE ||
		    code == CKR_ATTRIBUTE_TYPE_INVALID) {
			template[i].ulValueLen = (CK_ULONG)-1;
			rv = code;

		} else if(code == CKR_BUFFER_TOO_SMALL) {
			rv = code;


		} else if (code != CKR_OK) {
			rv = code;
			break;
		}
	}

	return rv;
}
