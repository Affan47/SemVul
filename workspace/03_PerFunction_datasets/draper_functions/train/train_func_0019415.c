doc_probe_device(struct docg3_cascade *cascade, int floor, struct device *dev)
{
	int ret, bbt_nbpages;
	u16 chip_id, chip_id_inv;
	struct docg3 *docg3;
	struct mtd_info *mtd;

	ret = -ENOMEM;
	docg3 = kzalloc(sizeof(struct docg3), GFP_KERNEL);
	if (!docg3)
		goto nomem1;
	mtd = kzalloc(sizeof(struct mtd_info), GFP_KERNEL);
	if (!mtd)
		goto nomem2;
	mtd->priv = docg3;
	mtd->dev.parent = dev;
	bbt_nbpages = DIV_ROUND_UP(docg3->max_block + 1,
				   8 * DOC_LAYOUT_PAGE_SIZE);
	docg3->bbt = kzalloc(bbt_nbpages * DOC_LAYOUT_PAGE_SIZE, GFP_KERNEL);
	if (!docg3->bbt)
		goto nomem3;

	docg3->dev = dev;
	docg3->device_id = floor;
	docg3->cascade = cascade;
	doc_set_device_id(docg3, docg3->device_id);
	if (!floor)
		doc_set_asic_mode(docg3, DOC_ASICMODE_RESET);
	doc_set_asic_mode(docg3, DOC_ASICMODE_NORMAL);

	chip_id = doc_register_readw(docg3, DOC_CHIPID);
	chip_id_inv = doc_register_readw(docg3, DOC_CHIPID_INV);

	ret = 0;
	if (chip_id != (u16)(~chip_id_inv)) {
		goto nomem4;
	}

	switch (chip_id) {
	case DOC_CHIPID_G3:
		doc_info("Found a G3 DiskOnChip at addr %p, floor %d\n",
			 docg3->cascade->base, floor);
		break;
	default:
		doc_err("Chip id %04x is not a DiskOnChip G3 chip\n", chip_id);
		goto nomem4;
	}

	ret = doc_set_driver_info(chip_id, mtd);
	if (ret)
		goto nomem4;

	doc_hamming_ecc_init(docg3, DOC_LAYOUT_OOB_PAGEINFO_SZ);
	doc_reload_bbt(docg3);
	return mtd;

nomem4:
	kfree(docg3->bbt);
nomem3:
	kfree(mtd);
nomem2:
	kfree(docg3);
nomem1:
	return ERR_PTR(ret);
}
