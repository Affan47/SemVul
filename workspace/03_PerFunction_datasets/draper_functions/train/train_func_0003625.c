spi_nor_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	struct spi_nor *nor = mtd_to_spi_nor(mtd);
	u32 addr, len;
	uint32_t rem;
	int ret;

	dev_dbg(nor->dev, "at 0x%llx, len %lld\n", (long long)instr->addr,
			(long long)instr->len);

	div_u64_rem(instr->len, mtd->erasesize, &rem);
	if (rem)
		return -EINVAL;

	addr = instr->addr;
	len = instr->len;

	ret = spi_nor_lock_and_prep(nor, SPI_NOR_OPS_ERASE);
	if (ret)
		return ret;


	if (len == mtd->size) {
		unsigned long timeout;

		write_enable(nor);

		if (erase_chip(nor)) {
			ret = -EIO;
			goto erase_err;
		}


		timeout = max(CHIP_ERASE_2MB_READY_WAIT_JIFFIES,
			      CHIP_ERASE_2MB_READY_WAIT_JIFFIES *
			      (unsigned long)(mtd->size / SZ_2M));
		ret = spi_nor_wait_till_ready_with_timeout(nor, timeout);
		if (ret)
			goto erase_err;


	} else {
		while (len) {
			write_enable(nor);

			if (nor->erase(nor, addr)) {
				ret = -EIO;
				goto erase_err;
			}

			addr += mtd->erasesize;
			len -= mtd->erasesize;

			ret = spi_nor_wait_till_ready(nor);
			if (ret)
				goto erase_err;
		}
	}

	write_disable(nor);

	spi_nor_unlock_and_unprep(nor, SPI_NOR_OPS_ERASE);

	instr->state = MTD_ERASE_DONE;
	mtd_erase_callback(instr);

	return ret;

erase_err:
	spi_nor_unlock_and_unprep(nor, SPI_NOR_OPS_ERASE);
	instr->state = MTD_ERASE_FAILED;
	return ret;
}
