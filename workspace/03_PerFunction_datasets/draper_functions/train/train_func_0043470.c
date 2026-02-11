swmathbox_init(void)
{
	UINT8 *src = memory_region(REGION_PROMS);
	int cnt, val;

	for (cnt = 0; cnt < 1024; cnt++)
	{

		val  = (src[0x0c00 + cnt]      ) & 0x000f;
		val |= (src[0x0800 + cnt] <<  4) & 0x00f0;
		val |= (src[0x0400 + cnt] <<  8) & 0x0f00;
		val |= (src[0x0000 + cnt] << 12) & 0xf000;


		PROM_STR[cnt] = (val >> 8) & 0x00ff;
		PROM_MAS[cnt] =  val       & 0x007f;
		PROM_AM[cnt]  = (val >> 7) & 0x0001;
	}
}
