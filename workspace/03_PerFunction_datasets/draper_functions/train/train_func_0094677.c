Identify_Cyrix (struct cpudata *cpu)
{
	unsigned long eax, ebx, ecx, edx;

	cpu->vendor = VENDOR_CYRIX;


	if (cpu->maxi < 1)
		return;

	cpuid (cpu->number, 1, &eax, &ebx, &ecx, &edx);
	cpu->stepping = eax & 0xf;
	cpu->model = (eax >> 4) & 0xf;
	cpu->family = (eax >> 8) & 0xf;

	switch (tuple(cpu) & 0xff0) {
		case 0x450:	sprintf (cpu->name, "%s", "MediaGX");
					break;

		case 0x520:	sprintf (cpu->name, "%s", "6x86");
					break;
		case 0x524:	sprintf (cpu->name, "%s", "GXm");
					break;

		case 0x600:	sprintf (cpu->name, "%s", "6x86/MX");
					break;
		case 0x620:	sprintf (cpu->name, "%s", "MII");
					break;
		default:	sprintf (cpu->name, "%s", "Unknown CPU");
					break;
	}


	if (cpu->maxei < 0x80000000)
		return;

	if (cpu->maxei >= 0x80000001) {
		cpuid (cpu->number, 0x80000001, &eax, &ebx, &ecx, &edx);
		cpu->stepping = eax & 0xf;
		cpu->model = (eax >> 4) & 0xf;
		cpu->family = (eax >> 8) & 0xf;

		switch (cpu->family) {
			case 4:	sprintf (cpu->name, "MediaGX");
					break;
			case 5:	sprintf (cpu->name, "6x86/GXm");
					break;
			case 6:	sprintf (cpu->name, "6x86/MX");
					break;
		}
	}
}
