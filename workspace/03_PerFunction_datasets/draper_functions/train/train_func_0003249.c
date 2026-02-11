fixup_LH28F640BF(struct mtd_info *mtd)
{
	struct map_info *map = mtd->priv;
	struct cfi_private *cfi = map->fldrv_priv;
	struct cfi_pri_intelext *extp = cfi->cmdset_priv;


	if (is_LH28F640BF(cfi)) {
		printk(KERN_INFO "Reset Partition Config. Register: 1 Partition of 4 planes\n");
		map_write(map, CMD(0x60), 0);
		map_write(map, CMD(0x04), 0);


		printk(KERN_INFO "cfi_cmdset_0001: Simultaneous Operations disabled\n");
		extp->FeatureSupport &= ~512;
	}
}
