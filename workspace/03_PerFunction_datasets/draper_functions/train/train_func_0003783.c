_gck_module_info_match (GckModuleInfo *match, GckModuleInfo *info)
{


	g_return_val_if_fail (match, FALSE);
	g_return_val_if_fail (info, FALSE);

	return (match_info_string (match->library_description, info->library_description) &&
	        match_info_string (match->manufacturer_id, info->manufacturer_id));
}
