count_roms(const struct RomModule *romp)
{
	const struct RomModule *region, *rom;
	int count = 0;


	int this_bios = determine_bios_rom(Machine->gamedrv->bios);


	for (region = romp; region; region = rom_next_region(region))
		for (rom = rom_first_file(region); rom; rom = rom_next_file(rom))
			if (!ROM_GETBIOSFLAGS(romp) || (ROM_GETBIOSFLAGS(romp) == (this_bios+1)))
				count++;


	return count;
}
