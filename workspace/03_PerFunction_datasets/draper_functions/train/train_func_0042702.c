param_setup_earlycon(char *buf)
{
	int err;


	if (!buf || !buf[0]) {
		if (IS_ENABLED(CONFIG_ACPI_SPCR_TABLE)) {
			earlycon_init_is_deferred = true;
			return 0;
		} else {
			return early_init_dt_scan_chosen_stdout();
		}
	}

	err = setup_earlycon(buf);
	if (err == -ENOENT || err == -EALREADY)
		return 0;
	return err;
}
