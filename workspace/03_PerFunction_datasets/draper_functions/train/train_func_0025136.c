aliens_banking( int lines )
{
	unsigned char *RAM = memory_region(REGION_CPU1);
	int offs = 0x18000;


	if (lines & 0x10) offs -= 0x8000;

	offs += (lines & 0x0f)*0x2000;
	cpu_setbank( 1, &RAM[offs] );
}
