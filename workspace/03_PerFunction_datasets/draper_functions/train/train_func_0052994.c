bnx2x_84833_common_init_phy(struct bnx2x *bp,
						u32 shmem_base_path[],
						u32 shmem2_base_path[],
						u8 phy_index,
						u32 chip_id)
{
	u8 reset_gpios;
	reset_gpios = bnx2x_84833_get_reset_gpios(bp, shmem_base_path, chip_id);
	bnx2x_set_mult_gpio(bp, reset_gpios, MISC_REGISTERS_GPIO_OUTPUT_LOW);
	udelay(10);
	bnx2x_set_mult_gpio(bp, reset_gpios, MISC_REGISTERS_GPIO_OUTPUT_HIGH);
	DP(NETIF_MSG_LINK, "84833 reset pulse on pin values 0x%x\n",
		reset_gpios);
	return 0;
}
