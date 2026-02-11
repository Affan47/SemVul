cvs_speech_rom_read_bit(void)
{
	unsigned char *ROM = memory_region(REGION_SOUND1);
    int bit;

	speech_rom_address %= memory_region_length(REGION_SOUND1);

	bit = (ROM[speech_rom_address] >> speech_rom_bit ) & 1;

    speech_rom_bit++;
    if(speech_rom_bit == 8)
    {
		speech_rom_address++;
        speech_rom_bit = 0;
    }

	return bit;
}
