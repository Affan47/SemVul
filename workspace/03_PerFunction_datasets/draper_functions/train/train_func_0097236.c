show_info(struct cpudata *cpu)
{
	if (silent)
		return;

	if (show_registers) {
		dumpregs (cpu->number, 0, cpu->maxi);
		if (cpu->maxei >=0x80000000)
			dumpregs (cpu->number, 0x80000000, cpu->maxei);

		if (cpu->maxei2 >=0xC0000000)
			dumpregs (cpu->number, 0xC0000000, cpu->maxei2);
	}

	switch (cpu->vendor) {
	case VENDOR_AMD:
		display_AMD_info(cpu);
		break;

	case VENDOR_CYRIX:
		display_Cyrix_info(cpu);
		break;

	case VENDOR_CENTAUR:
		display_IDT_info(cpu);
		break;

	case VENDOR_INTEL:
		display_Intel_info(cpu);
		break;

	case VENDOR_NATSEMI:
		display_NatSemi_info(cpu);
		break;

	case VENDOR_RISE:
		display_RiSE_info(cpu);
		break;

	case VENDOR_SIS:
		display_SiS_info(cpu);
		break;

	default:
		break;
	}

	if (show_connector)
		decode_connector (cpu->connector);

	if (show_urls) {
		if (cpu->datasheet_url != NULL)
			printf ("Datasheet: %s\n", cpu->datasheet_url);

		if (cpu->errata_url != NULL)
			printf ("Errata: %s\n", cpu->errata_url);

		printf ("\n");
	}

	if (!user_is_root)
		return;

	if (show_mtrr)
		dump_mtrrs(cpu);
}
