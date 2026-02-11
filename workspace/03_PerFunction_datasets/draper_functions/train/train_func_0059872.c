toggle_dos_compatibility_flag(void)
{
	dos_compatible_flag = 1 - dos_compatible_flag;
	if (dos_compatible_flag) {
		sector_offset = g_sectors;
		printf("DOS Compatibility flag is set\n");
	} else {
		sector_offset = 1;
		printf("DOS Compatibility flag is not set\n");
	}
}
