megasas_get_map_info(struct megasas_instance *instance)
{
	struct fusion_context *fusion = instance->ctrl_context;

	fusion->fast_path_io = 0;
	if (!megasas_get_ld_map_info(instance)) {
		if (MR_ValidateMapInfo(instance)) {
			fusion->fast_path_io = 1;
			return 0;
		}
	}
	return 1;
}
