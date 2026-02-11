cfi_ppb_unlock(struct mtd_info *mtd, loff_t ofs,
					 uint64_t len)
{
	struct mtd_erase_region_info *regions = mtd->eraseregions;
	struct map_info *map = mtd->priv;
	struct cfi_private *cfi = map->fldrv_priv;
	struct ppb_lock *sect;
	unsigned long adr;
	loff_t offset;
	uint64_t length;
	int chipnum;
	int i;
	int sectors;
	int ret;


	sect = kzalloc(MAX_SECTORS * sizeof(struct ppb_lock), GFP_KERNEL);
	if (!sect)
		return -ENOMEM;


	i = 0;
	chipnum = 0;
	adr = 0;
	sectors = 0;
	offset = 0;
	length = mtd->size;

	while (length) {
		int size = regions[i].erasesize;


		if ((adr < ofs) || (adr >= (ofs + len))) {
			sect[sectors].chip = &cfi->chips[chipnum];
			sect[sectors].offset = offset;
			sect[sectors].locked = do_ppb_xxlock(
				map, &cfi->chips[chipnum], adr, 0,
				DO_XXLOCK_ONEBLOCK_GETLOCK);
		}

		adr += size;
		offset += size;
		length -= size;

		if (offset == regions[i].offset + size * regions[i].numblocks)
			i++;

		if (adr >> cfi->chipshift) {
			adr = 0;
			chipnum++;

			if (chipnum >= cfi->numchips)
				break;
		}

		sectors++;
		if (sectors >= MAX_SECTORS) {
			printk(KERN_ERR "Only %d sectors for PPB locking supported!\n",
			       MAX_SECTORS);
			kfree(sect);
			return -EINVAL;
		}
	}


	ret = cfi_varsize_frob(mtd, do_ppb_xxlock, ofs, len,
			       DO_XXLOCK_ONEBLOCK_UNLOCK);
	if (ret) {
		kfree(sect);
		return ret;
	}


	for (i = 0; i < sectors; i++) {
		if (sect[i].locked)
			do_ppb_xxlock(map, sect[i].chip, sect[i].offset, 0,
				      DO_XXLOCK_ONEBLOCK_LOCK);
	}

	kfree(sect);
	return ret;
}
