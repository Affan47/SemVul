snd_sbmixer_suspend(struct snd_sb *chip)
{
	switch (chip->hardware) {
	case SB_HW_20:
	case SB_HW_201:
		save_mixer(chip, sb20_saved_regs, ARRAY_SIZE(sb20_saved_regs));
		break;
	case SB_HW_PRO:
	case SB_HW_JAZZ16:
		save_mixer(chip, sbpro_saved_regs, ARRAY_SIZE(sbpro_saved_regs));
		break;
	case SB_HW_16:
	case SB_HW_ALS100:
	case SB_HW_CS5530:
		save_mixer(chip, sb16_saved_regs, ARRAY_SIZE(sb16_saved_regs));
		break;
	case SB_HW_ALS4000:
		save_mixer(chip, als4000_saved_regs, ARRAY_SIZE(als4000_saved_regs));
		break;
	case SB_HW_DT019X:
		save_mixer(chip, dt019x_saved_regs, ARRAY_SIZE(dt019x_saved_regs));
		break;
	default:
		break;
	}
}
