block2mtd_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	struct block2mtd_dev *dev = mtd->priv;
	size_t from = instr->addr;
	size_t len = instr->len;
	int err;

	instr->state = MTD_ERASING;
	mutex_lock(&dev->write_mutex);
	err = _block2mtd_erase(dev, from, len);
	mutex_unlock(&dev->write_mutex);
	if (err) {
		pr_err("erase failed err = %d\n", err);
		instr->state = MTD_ERASE_FAILED;
	} else
		instr->state = MTD_ERASE_DONE;

	mtd_erase_callback(instr);
	return err;
}
