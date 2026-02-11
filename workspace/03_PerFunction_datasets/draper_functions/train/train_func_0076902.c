cfi_staa_lock(struct mtd_info *mtd, loff_t ofs, uint64_t len)
{
	struct map_info *map = mtd->priv;
	struct cfi_private *cfi = map->fldrv_priv;
	unsigned long adr;
	int chipnum, ret = 0;
#ifdef DEBUG_LOCK_BITS
	int ofs_factor = cfi->interleave * cfi->device_type;
#endif

	if (ofs & (mtd->erasesize - 1))
		return -EINVAL;

	if (len & (mtd->erasesize -1))
		return -EINVAL;

	chipnum = ofs >> cfi->chipshift;
	adr = ofs - (chipnum << cfi->chipshift);

	while(len) {

#ifdef DEBUG_LOCK_BITS
		cfi_send_gen_cmd(0x90, 0x55, 0, map, cfi, cfi->device_type, NULL);
		printk("before lock: block status register is %x\n",cfi_read_query(map, adr+(2*ofs_factor)));
		cfi_send_gen_cmd(0xff, 0x55, 0, map, cfi, cfi->device_type, NULL);
#endif

		ret = do_lock_oneblock(map, &cfi->chips[chipnum], adr);

#ifdef DEBUG_LOCK_BITS
		cfi_send_gen_cmd(0x90, 0x55, 0, map, cfi, cfi->device_type, NULL);
		printk("after lock: block status register is %x\n",cfi_read_query(map, adr+(2*ofs_factor)));
		cfi_send_gen_cmd(0xff, 0x55, 0, map, cfi, cfi->device_type, NULL);
#endif

		if (ret)
			return ret;

		adr += mtd->erasesize;
		len -= mtd->erasesize;

		if (adr >> cfi->chipshift) {
			adr = 0;
			chipnum++;

			if (chipnum >= cfi->numchips)
				break;
		}
	}
	return 0;
}
