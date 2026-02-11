fat_ent_access_init(struct super_block *sb)
{
	struct msdos_sb_info *sbi = MSDOS_SB(sb);

	mutex_init(&sbi->fat_lock);

	switch (sbi->fat_bits) {
	case 32:
		sbi->fatent_shift = 2;
		sbi->fatent_ops = &fat32_ops;
		break;
	case 16:
		sbi->fatent_shift = 1;
		sbi->fatent_ops = &fat16_ops;
		break;
	case 12:
		sbi->fatent_shift = -1;
		sbi->fatent_ops = &fat12_ops;
		break;
	}
}
