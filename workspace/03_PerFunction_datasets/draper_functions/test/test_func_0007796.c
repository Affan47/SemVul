vgck_single(struct cmd_context *cmd __attribute__((unused)),
		       const char *vg_name,
		       struct volume_group *vg,
		       void *handle __attribute__((unused)))
{
	if (!vg_check_status(vg, EXPORTED_VG)) {
		stack;
		return ECMD_FAILED;
	}

	if (!vg_validate(vg)) {
		stack;
		return ECMD_FAILED;
	}

	if (vg_missing_pv_count(vg)) {
		log_error("The volume group is missing %d physical volumes.",
			  vg_missing_pv_count(vg));
		return ECMD_FAILED;
	}

	return ECMD_PROCESSED;
}
