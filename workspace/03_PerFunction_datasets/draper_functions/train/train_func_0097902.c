gpk_application_state_get_icon (PkBitfield state)
{
	if (state == 0)
		return gpk_info_enum_to_icon_name (PK_INFO_ENUM_AVAILABLE);

	if (state == pk_bitfield_value (GPK_STATE_INSTALLED))
		return gpk_info_enum_to_icon_name (PK_INFO_ENUM_INSTALLED);

	if (state == pk_bitfield_value (GPK_STATE_IN_LIST))
		return gpk_info_enum_to_icon_name (PK_INFO_ENUM_INSTALLING);

	if (state == pk_bitfield_from_enums (GPK_STATE_INSTALLED, GPK_STATE_IN_LIST, -1))
		return gpk_info_enum_to_icon_name (PK_INFO_ENUM_REMOVING);

	if (state == pk_bitfield_value (GPK_STATE_COLLECTION))
		return gpk_info_enum_to_icon_name (PK_INFO_ENUM_COLLECTION_AVAILABLE);

	if (state == pk_bitfield_from_enums (GPK_STATE_INSTALLED, GPK_STATE_COLLECTION, -1))
		return gpk_info_enum_to_icon_name (PK_INFO_ENUM_COLLECTION_INSTALLED);

	if (state == pk_bitfield_from_enums (GPK_STATE_IN_LIST, GPK_STATE_INSTALLED, GPK_STATE_COLLECTION, -1))
		return gpk_info_enum_to_icon_name (PK_INFO_ENUM_REMOVING);

	if (state == pk_bitfield_from_enums (GPK_STATE_IN_LIST, GPK_STATE_COLLECTION, -1))
		return gpk_info_enum_to_icon_name (PK_INFO_ENUM_INSTALLING);

	return NULL;
}
