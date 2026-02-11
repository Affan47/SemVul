AllocMapRAM(void)
{
	if (MEMORY_enable_mapram && Atari800_machine_type == Atari800_MACHINE_XLXE
	    && MEMORY_ram_size > 20) {
		if (mapram_memory == NULL)
			mapram_memory = (UBYTE *)Util_malloc(0x800);
	}
	else if (mapram_memory != NULL) {
		free(mapram_memory);
		mapram_memory = NULL;
	}
}
