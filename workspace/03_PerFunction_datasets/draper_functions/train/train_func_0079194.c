stm_get_locked_range(struct spi_nor *nor, u8 sr, loff_t *ofs,
				 uint64_t *len)
{
	struct mtd_info *mtd = &nor->mtd;
	u8 mask = SR_BP2 | SR_BP1 | SR_BP0;
	int shift = ffs(mask) - 1;
	int pow;

	if (!(sr & mask)) {

		*ofs = 0;
		*len = 0;
	} else {
		pow = ((sr & mask) ^ mask) >> shift;
		*len = mtd->size >> pow;
		*ofs = mtd->size - *len;
	}
}
