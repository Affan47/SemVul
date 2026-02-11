chk_ucode_version(unsigned int cpu)
{
	struct cpuinfo_x86 *c = &cpu_data(cpu);


	if (c->x86_model == 0xe && c->x86_mask < 0xc && c->microcode < 0x39) {
		pr_err("Errata AE18 not fixed, update BIOS or microcode of the CPU!\n");
		return -ENODEV;
	}
	return 0;
}
