rom_load(const struct RomModule *romp)
{
	const struct RomModule *regionlist[REGION_MAX];
	const struct RomModule *region;
	static struct rom_load_data romdata;
	int regnum;


	for (regnum = 0;regnum < REGION_MAX;regnum++)
		regionlist[regnum] = NULL;


	memset(&romdata, 0, sizeof(romdata));
	romdata.romstotal = count_roms(romp);


	memset(disk_handle, 0, sizeof(disk_handle));


	system_bios = determine_bios_rom(Machine->gamedrv->bios);


	for (region = romp, regnum = 0; region; region = rom_next_region(region), regnum++)
	{
		int regiontype = ROMREGION_GETTYPE(region);

		debugload("Processing region %02X (length=%X)\n", regiontype, ROMREGION_GETLENGTH(region));


		if (!ROMENTRY_ISREGION(region))
		{
			printf("Error: missing ROM_REGION header\n");
			return 1;
		}


		if (Machine->sample_rate == 0 && ROMREGION_ISSOUNDONLY(region))
			continue;


		if (new_memory_region(regiontype, ROMREGION_GETLENGTH(region), ROMREGION_GETFLAGS(region)))
		{
			printf("Error: unable to allocate memory for region %d\n", regiontype);
			return 1;
		}


		romdata.regionlength = memory_region_length(regiontype);
		romdata.regionbase = memory_region(regiontype);
		debugload("Allocated %X bytes @ %08X\n", romdata.regionlength, (int)romdata.regionbase);


		if (ROMREGION_ISERASE(region))
			memset(romdata.regionbase, ROMREGION_GETERASEVAL(region), romdata.regionlength);


		else if (romdata.regionlength <= 0x400000)
			memset(romdata.regionbase, 0, romdata.regionlength);

#ifdef MAME_DEBUG

		else
			fill_random(romdata.regionbase, romdata.regionlength);
#endif


		if (ROMREGION_ISROMDATA(region))
		{
			if (!process_rom_entries(&romdata, region + 1))
				return 1;
		}
		else if (ROMREGION_ISDISKDATA(region))
		{
			if (!process_disk_entries(&romdata, region + 1))
				return 1;
		}


		if (regiontype < REGION_MAX)
			regionlist[regiontype] = region;
	}


	for (regnum = 0; regnum < REGION_MAX; regnum++)
		if (regionlist[regnum])
		{
			debugload("Post-processing region %02X\n", regnum);
			romdata.regionlength = memory_region_length(regnum);
			romdata.regionbase = memory_region(regnum);
			region_post_process(&romdata, regionlist[regnum]);
		}


	return display_rom_load_results(&romdata);
}
