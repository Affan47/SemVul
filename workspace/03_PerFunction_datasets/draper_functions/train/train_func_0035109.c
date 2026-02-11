tboot_shutdown(u32 shutdown_type)
{
	void (*shutdown)(void);

	if (!tboot_enabled())
		return;


	if (!tboot_pg_dir)
		return;


	if (shutdown_type == TB_SHUTDOWN_S3)
		if (tboot_setup_sleep())
			return;

	tboot->shutdown_type = shutdown_type;

	switch_to_tboot_pt();

	shutdown = (void(*)(void))(unsigned long)tboot->shutdown_entry;
	shutdown();


	while (1)
		halt();
}
