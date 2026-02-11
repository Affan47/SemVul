rtsx_delink_stage(struct rtsx_chip *chip)
{
	int delink_stage1_cnt, delink_stage2_cnt, delink_stage3_cnt;
	int enter_L1;

	if (!chip->auto_delink_en || !chip->auto_delink_allowed ||
	    chip->card_ready || chip->card_ejected || chip->sd_io) {
		chip->auto_delink_cnt = 0;
		return;
	}

	enter_L1 = chip->auto_delink_in_L1 &&
		(chip->aspm_l0s_l1_en || chip->ss_en);

	delink_stage1_cnt = chip->delink_stage1_step;
	delink_stage2_cnt = delink_stage1_cnt + chip->delink_stage2_step;
	delink_stage3_cnt = delink_stage2_cnt + chip->delink_stage3_step;

	if (chip->auto_delink_cnt > delink_stage3_cnt)
		return;

	if (chip->auto_delink_cnt == delink_stage1_cnt)
		rtsx_delink_stage1(chip, enter_L1, delink_stage3_cnt);

	if (chip->auto_delink_cnt == delink_stage2_cnt) {
		dev_dbg(rtsx_dev(chip), "Try to do force delink\n");

		if (enter_L1)
			rtsx_exit_L1(chip);

		if (chip->asic_code && CHECK_PID(chip, 0x5208))
			rtsx_set_phy_reg_bit(chip, 0x1C, 2);

		rtsx_write_register(chip, CHANGE_LINK_STATE, 0x0A, 0x0A);
	}

	chip->auto_delink_cnt++;
}
