cfi_intelext_setup(struct mtd_info *mtd)
{
	struct map_info *map = mtd->priv;
	struct cfi_private *cfi = map->fldrv_priv;
	unsigned long offset = 0;
	int i,j;
	unsigned long devsize = (1<<cfi->cfiq->DevSize) * cfi->interleave;


	mtd->size = devsize * cfi->numchips;

	mtd->numeraseregions = cfi->cfiq->NumEraseRegions * cfi->numchips;
	mtd->eraseregions = kmalloc(sizeof(struct mtd_erase_region_info)
			* mtd->numeraseregions, GFP_KERNEL);
	if (!mtd->eraseregions)
		goto setup_err;

	for (i=0; i<cfi->cfiq->NumEraseRegions; i++) {
		unsigned long ernum, ersize;
		ersize = ((cfi->cfiq->EraseRegionInfo[i] >> 8) & ~0xff) * cfi->interleave;
		ernum = (cfi->cfiq->EraseRegionInfo[i] & 0xffff) + 1;

		if (mtd->erasesize < ersize) {
			mtd->erasesize = ersize;
		}
		for (j=0; j<cfi->numchips; j++) {
			mtd->eraseregions[(j*cfi->cfiq->NumEraseRegions)+i].offset = (j*devsize)+offset;
			mtd->eraseregions[(j*cfi->cfiq->NumEraseRegions)+i].erasesize = ersize;
			mtd->eraseregions[(j*cfi->cfiq->NumEraseRegions)+i].numblocks = ernum;
			mtd->eraseregions[(j*cfi->cfiq->NumEraseRegions)+i].lockmap = kmalloc(ernum / 8 + 1, GFP_KERNEL);
		}
		offset += (ersize * ernum);
	}

	if (offset != devsize) {

		printk(KERN_WARNING "Sum of regions (%lx) != total size of set of interleaved chips (%lx)\n", offset, devsize);
		goto setup_err;
	}

	for (i=0; i<mtd->numeraseregions;i++){
		printk(KERN_DEBUG "erase region %d: offset=0x%llx,size=0x%x,blocks=%d\n",
		       i,(unsigned long long)mtd->eraseregions[i].offset,
		       mtd->eraseregions[i].erasesize,
		       mtd->eraseregions[i].numblocks);
	}

#ifdef CONFIG_MTD_OTP
	mtd->_read_fact_prot_reg = cfi_intelext_read_fact_prot_reg;
	mtd->_read_user_prot_reg = cfi_intelext_read_user_prot_reg;
	mtd->_write_user_prot_reg = cfi_intelext_write_user_prot_reg;
	mtd->_lock_user_prot_reg = cfi_intelext_lock_user_prot_reg;
	mtd->_get_fact_prot_info = cfi_intelext_get_fact_prot_info;
	mtd->_get_user_prot_info = cfi_intelext_get_user_prot_info;
#endif


	if (cfi_intelext_partition_fixup(mtd, &cfi) != 0)
		goto setup_err;

	__module_get(THIS_MODULE);
	register_reboot_notifier(&mtd->reboot_notifier);
	return mtd;

 setup_err:
	kfree(mtd->eraseregions);
	kfree(mtd);
	kfree(cfi->cmdset_priv);
	return NULL;
}
