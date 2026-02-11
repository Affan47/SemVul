tonga_update_uvd_dpm(struct pp_hwmgr *hwmgr, bool bgate)
{
	struct tonga_hwmgr *data = (struct tonga_hwmgr *)(hwmgr->backend);
	uint32_t mm_boot_level_offset, mm_boot_level_value;
	struct phm_ppt_v1_information *ptable_information = (struct phm_ppt_v1_information *)(hwmgr->pptable);

	if (!bgate) {
		data->smc_state_table.UvdBootLevel = (uint8_t) (ptable_information->mm_dep_table->count - 1);
		mm_boot_level_offset = data->dpm_table_start + offsetof(SMU72_Discrete_DpmTable, UvdBootLevel);
		mm_boot_level_offset /= 4;
		mm_boot_level_offset *= 4;
		mm_boot_level_value = cgs_read_ind_register(hwmgr->device, CGS_IND_REG__SMC, mm_boot_level_offset);
		mm_boot_level_value &= 0x00FFFFFF;
		mm_boot_level_value |= data->smc_state_table.UvdBootLevel << 24;
		cgs_write_ind_register(hwmgr->device, CGS_IND_REG__SMC, mm_boot_level_offset, mm_boot_level_value);

		if (!phm_cap_enabled(hwmgr->platform_descriptor.platformCaps, PHM_PlatformCaps_UVDDPM) ||
		    phm_cap_enabled(hwmgr->platform_descriptor.platformCaps, PHM_PlatformCaps_StablePState))
			smum_send_msg_to_smc_with_parameter(hwmgr->smumgr,
						PPSMC_MSG_UVDDPM_SetEnabledMask,
						(uint32_t)(1 << data->smc_state_table.UvdBootLevel));
	}

	return tonga_enable_disable_uvd_dpm(hwmgr, !bgate);
}
