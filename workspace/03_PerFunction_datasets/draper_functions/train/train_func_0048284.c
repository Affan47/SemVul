stm_unlock(struct spi_nor *nor, loff_t ofs, uint64_t len)
{
	struct mtd_info *mtd = &nor->mtd;
	uint8_t status_old, status_new;
	u8 mask = SR_BP2 | SR_BP1 | SR_BP0;
	u8 shift = ffs(mask) - 1, pow, val;

	status_old = read_sr(nor);


	if (stm_is_locked_sr(nor, ofs - mtd->erasesize, mtd->erasesize,
			     status_old))
		return -EINVAL;


	pow = ilog2(mtd->size) - order_base_2(mtd->size - (ofs + len));
	if (ofs + len == mtd->size) {
		val = 0;
	} else {
		val = mask - (pow << shift);

		if (val & ~mask)
			return -EINVAL;
	}

	status_new = (status_old & ~mask) | val;


	if ((status_new & mask) >= (status_old & mask))
		return -EINVAL;

	write_enable(nor);
	return write_sr(nor, status_new);
}
