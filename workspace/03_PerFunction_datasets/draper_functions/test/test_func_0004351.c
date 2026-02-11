default_find_bmc(void)
{
	struct smi_info *info;
	int             i;

	for (i = 0; ; i++) {
		if (!ipmi_defaults[i].port)
			break;
#ifdef CONFIG_PPC
		if (check_legacy_ioport(ipmi_defaults[i].port))
			continue;
#endif
		info = smi_info_alloc();
		if (!info)
			return;

		info->addr_source = SI_DEFAULT;

		info->si_type = ipmi_defaults[i].type;
		info->io_setup = port_setup;
		info->io.addr_data = ipmi_defaults[i].port;
		info->io.addr_type = IPMI_IO_ADDR_SPACE;

		info->io.addr = NULL;
		info->io.regspacing = DEFAULT_REGSPACING;
		info->io.regsize = DEFAULT_REGSPACING;
		info->io.regshift = 0;

		if (add_smi(info) == 0) {
			if ((try_smi_init(info)) == 0) {

				printk(KERN_INFO PFX "Found default %s"
				" state machine at %s address 0x%lx\n",
				si_to_str[info->si_type],
				addr_space_to_str[info->io.addr_type],
				info->io.addr_data);
			} else
				cleanup_one_si(info);
		} else {
			kfree(info);
		}
	}
}
