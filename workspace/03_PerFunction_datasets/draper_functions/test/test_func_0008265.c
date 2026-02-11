ndmp_9to4_name (
  ndmp9_name *name9,
  ndmp4_name *name4)
{
	name4->original_path = NDMOS_API_STRDUP(name9->original_path);
	name4->destination_path = NDMOS_API_STRDUP(name9->destination_path);
	name4->name = NDMOS_API_STRDUP("");
	name4->other_name =  NDMOS_API_STRDUP("");

	if (name9->fh_info.valid == NDMP9_VALIDITY_VALID) {
		name4->fh_info = name9->fh_info.value;
	} else {
		name4->fh_info = NDMP_INVALID_U_QUAD;
	}

	name4->node = NDMP_INVALID_U_QUAD;

	return 0;
}
