tboot_extended_sleep(u8 sleep_state, u32 val_a, u32 val_b)
{
	if (!tboot_enabled())
		return 0;

	pr_warning("tboot is not able to suspend on platforms with reduced hardware sleep (ACPIv5)");
	return -ENODEV;
}
