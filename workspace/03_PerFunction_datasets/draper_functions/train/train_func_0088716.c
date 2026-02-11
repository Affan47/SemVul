smum_init(struct amd_pp_init *pp_init, struct pp_instance *handle)
{
	struct pp_smumgr *smumgr;

	if ((handle == NULL) || (pp_init == NULL))
		return -EINVAL;

	smumgr = kzalloc(sizeof(struct pp_smumgr), GFP_KERNEL);
	if (smumgr == NULL)
		return -ENOMEM;

	smumgr->device = pp_init->device;
	smumgr->chip_family = pp_init->chip_family;
	smumgr->chip_id = pp_init->chip_id;
	smumgr->hw_revision = pp_init->rev_id;
	smumgr->usec_timeout = AMD_MAX_USEC_TIMEOUT;
	smumgr->reload_fw = 1;
	handle->smu_mgr = smumgr;

	switch (smumgr->chip_family) {
	case AMD_FAMILY_CZ:
		cz_smum_init(smumgr);
		break;
	case AMD_FAMILY_VI:
		switch (smumgr->chip_id) {
		case CHIP_TONGA:
			tonga_smum_init(smumgr);
			break;
		case CHIP_FIJI:
			fiji_smum_init(smumgr);
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		kfree(smumgr);
		return -EINVAL;
	}

	return 0;
}
