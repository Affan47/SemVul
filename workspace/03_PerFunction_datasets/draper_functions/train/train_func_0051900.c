msole_vt_name (GsfMSOleVariantType type)
{
	static char const *names[] = {
		"VT_EMPTY",	"VT_NULL",	"VT_I2",	"VT_I4",	"VT_R4",
		"VT_R8",	"VT_CY",	"VT_DATE",	"VT_BSTR",	"VT_DISPATCH",
		"VT_ERROR",	"VT_BOOL",	"VT_VARIANT",	"VT_UNKNOWN",	"VT_DECIMAL",
		NULL,		"VT_I1",	"VT_UI1",	"VT_UI2",	"VT_UI4",
		"VT_I8",	"VT_UI8",	"VT_INT",	"VT_UINT",	"VT_VOID",
		"VT_HRESULT",	"VT_PTR",	"VT_SAFEARRAY",	"VT_CARRAY",	"VT_USERDEFINED",
		"VT_LPSTR",	"VT_LPWSTR",
	};
	static char const *names2[] = {
		"VT_FILETIME",
		"VT_BLOB",	"VT_STREAM",	"VT_STORAGE",	"VT_STREAMED_OBJECT",
		"VT_STORED_OBJECT", "VT_BLOB_OBJECT", "VT_CF",	"VT_CLSID"
	};

	type &= ~VT_VECTOR;
	if (type <= VT_LPWSTR)
		return names[type];
	g_return_val_if_fail (type >= VT_FILETIME, "_UNKNOWN_");
	g_return_val_if_fail (type <= VT_CLSID, "_UNKNOWN_");
	return names2[type-VT_FILETIME];
}
