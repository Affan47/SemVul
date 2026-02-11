gpk_update_viewer_info_is_update_enum (PkInfoEnum info)
{
	gboolean ret = FALSE;
	switch (info) {
	case PK_INFO_ENUM_LOW:
	case PK_INFO_ENUM_NORMAL:
	case PK_INFO_ENUM_IMPORTANT:
	case PK_INFO_ENUM_SECURITY:
	case PK_INFO_ENUM_BUGFIX:
	case PK_INFO_ENUM_ENHANCEMENT:
	case PK_INFO_ENUM_BLOCKED:
		ret = TRUE;
		break;
	default:
		break;
	}
	return ret;
}
