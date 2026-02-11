pirates_decrypt_p(void)
{
    int rom_size;
    UINT8 *buf, *rom;
    int i;

    rom_size = memory_region_length(REGION_GFX1);

    buf = malloc(rom_size);

    if (!buf) return;

    rom = memory_region(REGION_GFX1);
    memcpy (buf, rom, rom_size);

    for (i=0; i<rom_size/4; i++)
    {
		int adr = BITSWAP24(i,23,22,21,20,19,18,10,2,5,9,7,13,16,14,11,4,1,6,12,17,3,0,15,8);
		rom[adr+0*(rom_size/4)] = BITSWAP8(buf[i+0*(rom_size/4)], 2,3,4,0,7,5,1,6);
		rom[adr+1*(rom_size/4)] = BITSWAP8(buf[i+1*(rom_size/4)], 4,2,7,1,6,5,0,3);
		rom[adr+2*(rom_size/4)] = BITSWAP8(buf[i+2*(rom_size/4)], 1,4,7,0,3,5,6,2);
		rom[adr+3*(rom_size/4)] = BITSWAP8(buf[i+3*(rom_size/4)], 2,3,4,0,7,5,1,6);
    }
    free (buf);
}
