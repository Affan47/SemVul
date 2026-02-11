denali_irq_enable(struct denali_nand_info *denali,
							uint32_t int_mask)
{
	int i;

	for (i = 0; i < denali->max_banks; ++i)
		iowrite32(int_mask, denali->flash_reg + INTR_EN(i));
}
