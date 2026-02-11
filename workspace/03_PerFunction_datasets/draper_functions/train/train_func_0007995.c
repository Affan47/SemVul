wrap_C_DeriveKey (CK_SESSION_HANDLE handle, CK_MECHANISM_PTR mechanism,
                  CK_OBJECT_HANDLE base_key, CK_ATTRIBUTE_PTR template,
                  CK_ULONG count, CK_OBJECT_HANDLE_PTR key)
{
	Mapping map;
	CK_RV rv;

	rv = map_session_to_real (&handle, &map, NULL);
	if (rv != CKR_OK)
		return rv;
	return (map.funcs->C_DeriveKey) (handle, mechanism, base_key, template, count, key);
}
