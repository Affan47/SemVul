spi_read_int(u32 *int_status)
{
	int ret;

	if (g_spi.has_thrpt_enh) {
		ret = spi_internal_read(0xe840 - WILC_SPI_REG_BASE, int_status);
	} else {
		u32 tmp;
		u32 byte_cnt;

		ret = spi_read_reg(WILC_VMM_TO_HOST_SIZE, &byte_cnt);
		if (!ret) {
			PRINT_ER("[wilc spi]: Failed read WILC_VMM_TO_HOST_SIZE ...\n");
			goto _fail_;
		}
		tmp = (byte_cnt >> 2) & IRQ_DMA_WD_CNT_MASK;

		{
			int happended, j;

			j = 0;
			do {
				u32 irq_flags;

				happended = 0;

				spi_read_reg(0x1a90, &irq_flags);
				tmp |= ((irq_flags >> 27) << IRG_FLAGS_OFFSET);

				if (g_spi.nint > 5) {
					spi_read_reg(0x1a94, &irq_flags);
					tmp |= (((irq_flags >> 0) & 0x7) << (IRG_FLAGS_OFFSET + 5));
				}

				{
					u32 unkmown_mask;

					unkmown_mask = ~((1ul << g_spi.nint) - 1);

					if ((tmp >> IRG_FLAGS_OFFSET) & unkmown_mask) {
						PRINT_ER("[wilc spi]: Unexpected interrupt (2): j=%d, tmp=%x, mask=%x\n", j, tmp, unkmown_mask);
						happended = 1;
					}
				}
				j++;
			} while (happended);
		}

		*int_status = tmp;

	}

_fail_:
	return ret;
}
