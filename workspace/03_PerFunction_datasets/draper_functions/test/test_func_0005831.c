gpk_info_status_enum_to_string (GpkInfoStatusEnum info)
{
	if ((PkInfoEnum)info >= PK_INFO_ENUM_LAST)
		return gpk_info_enum_to_localised_past (info - PK_INFO_ENUM_LAST);
	return gpk_info_enum_to_localised_present (info);
}
