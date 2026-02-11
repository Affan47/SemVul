si_init_golden_registers(struct radeon_device *rdev)
{
	switch (rdev->family) {
	case CHIP_TAHITI:
		radeon_program_register_sequence(rdev,
						 tahiti_golden_registers,
						 (const u32)ARRAY_SIZE(tahiti_golden_registers));
		radeon_program_register_sequence(rdev,
						 tahiti_golden_rlc_registers,
						 (const u32)ARRAY_SIZE(tahiti_golden_rlc_registers));
		radeon_program_register_sequence(rdev,
						 tahiti_mgcg_cgcg_init,
						 (const u32)ARRAY_SIZE(tahiti_mgcg_cgcg_init));
		radeon_program_register_sequence(rdev,
						 tahiti_golden_registers2,
						 (const u32)ARRAY_SIZE(tahiti_golden_registers2));
		break;
	case CHIP_PITCAIRN:
		radeon_program_register_sequence(rdev,
						 pitcairn_golden_registers,
						 (const u32)ARRAY_SIZE(pitcairn_golden_registers));
		radeon_program_register_sequence(rdev,
						 pitcairn_golden_rlc_registers,
						 (const u32)ARRAY_SIZE(pitcairn_golden_rlc_registers));
		radeon_program_register_sequence(rdev,
						 pitcairn_mgcg_cgcg_init,
						 (const u32)ARRAY_SIZE(pitcairn_mgcg_cgcg_init));
		break;
	case CHIP_VERDE:
		radeon_program_register_sequence(rdev,
						 verde_golden_registers,
						 (const u32)ARRAY_SIZE(verde_golden_registers));
		radeon_program_register_sequence(rdev,
						 verde_golden_rlc_registers,
						 (const u32)ARRAY_SIZE(verde_golden_rlc_registers));
		radeon_program_register_sequence(rdev,
						 verde_mgcg_cgcg_init,
						 (const u32)ARRAY_SIZE(verde_mgcg_cgcg_init));
		radeon_program_register_sequence(rdev,
						 verde_pg_init,
						 (const u32)ARRAY_SIZE(verde_pg_init));
		break;
	case CHIP_OLAND:
		radeon_program_register_sequence(rdev,
						 oland_golden_registers,
						 (const u32)ARRAY_SIZE(oland_golden_registers));
		radeon_program_register_sequence(rdev,
						 oland_golden_rlc_registers,
						 (const u32)ARRAY_SIZE(oland_golden_rlc_registers));
		radeon_program_register_sequence(rdev,
						 oland_mgcg_cgcg_init,
						 (const u32)ARRAY_SIZE(oland_mgcg_cgcg_init));
		break;
	case CHIP_HAINAN:
		radeon_program_register_sequence(rdev,
						 hainan_golden_registers,
						 (const u32)ARRAY_SIZE(hainan_golden_registers));
		radeon_program_register_sequence(rdev,
						 hainan_golden_registers2,
						 (const u32)ARRAY_SIZE(hainan_golden_registers2));
		radeon_program_register_sequence(rdev,
						 hainan_mgcg_cgcg_init,
						 (const u32)ARRAY_SIZE(hainan_mgcg_cgcg_init));
		break;
	default:
		break;
	}
}
