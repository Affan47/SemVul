fiji_dpm_set_interrupt_state(void *private_data,
					 unsigned src_id, unsigned type,
					 int enabled)
{
	uint32_t cg_thermal_int;
	struct pp_hwmgr *hwmgr = ((struct pp_eventmgr *)private_data)->hwmgr;

	if (hwmgr == NULL)
		return -EINVAL;

	switch (type) {
	case AMD_THERMAL_IRQ_LOW_TO_HIGH:
		if (enabled) {
			cg_thermal_int = cgs_read_ind_register(hwmgr->device,
					CGS_IND_REG__SMC, ixCG_THERMAL_INT);
			cg_thermal_int |= CG_THERMAL_INT_CTRL__THERM_INTH_MASK_MASK;
			cgs_write_ind_register(hwmgr->device,
					CGS_IND_REG__SMC, ixCG_THERMAL_INT, cg_thermal_int);
		} else {
			cg_thermal_int = cgs_read_ind_register(hwmgr->device,
					CGS_IND_REG__SMC, ixCG_THERMAL_INT);
			cg_thermal_int &= ~CG_THERMAL_INT_CTRL__THERM_INTH_MASK_MASK;
			cgs_write_ind_register(hwmgr->device,
					CGS_IND_REG__SMC, ixCG_THERMAL_INT, cg_thermal_int);
		}
		break;

	case AMD_THERMAL_IRQ_HIGH_TO_LOW:
		if (enabled) {
			cg_thermal_int = cgs_read_ind_register(hwmgr->device,
					CGS_IND_REG__SMC, ixCG_THERMAL_INT);
			cg_thermal_int |= CG_THERMAL_INT_CTRL__THERM_INTL_MASK_MASK;
			cgs_write_ind_register(hwmgr->device,
					CGS_IND_REG__SMC, ixCG_THERMAL_INT, cg_thermal_int);
		} else {
			cg_thermal_int = cgs_read_ind_register(hwmgr->device,
					CGS_IND_REG__SMC, ixCG_THERMAL_INT);
			cg_thermal_int &= ~CG_THERMAL_INT_CTRL__THERM_INTL_MASK_MASK;
			cgs_write_ind_register(hwmgr->device,
					CGS_IND_REG__SMC, ixCG_THERMAL_INT, cg_thermal_int);
		}
		break;
	default:
		break;
	}
	return 0;
}
