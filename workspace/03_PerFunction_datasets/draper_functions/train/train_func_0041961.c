reset_controller(void)
{
	int	i;

	outb_p(4, HD_CMD);
	for (i = 0; i < 1000; i++) barrier();
	outb_p(hd_info[0].ctl & 0x0f, HD_CMD);
	for (i = 0; i < 1000; i++) barrier();
	if (drive_busy())
		printk("hd: controller still busy\n");
	else if ((hd_error = inb(HD_ERROR)) != 1)
		printk("hd: controller reset failed: %02x\n", hd_error);
}
