rv770_populate_smc_mvdd_table(struct radeon_device *rdev,
					 RV770_SMC_STATETABLE *table)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);

	if (pi->mvdd_control) {
		table->lowSMIO[MVDD_HIGH_INDEX] |=
			cpu_to_be32(pi->mvdd_low_smio[MVDD_HIGH_INDEX]);
		table->lowSMIO[MVDD_LOW_INDEX] |=
			cpu_to_be32(pi->mvdd_low_smio[MVDD_LOW_INDEX]);

		table->voltageMaskTable.highMask[RV770_SMC_VOLTAGEMASK_MVDD] = 0;
		table->voltageMaskTable.lowMask[RV770_SMC_VOLTAGEMASK_MVDD] =
			cpu_to_be32(pi->mvdd_mask_low);
	}

	return 0;
}
