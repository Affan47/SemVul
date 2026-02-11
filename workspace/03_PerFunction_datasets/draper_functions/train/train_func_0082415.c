pbillian_sh_start(const struct MachineSound *msound)
{
	int i;
	unsigned char *ROM = memory_region(REGION_SOUND1);
	channel = mixer_allocate_channel(50);
	mixer_set_name(channel,"Samples");
	samplebuf = auto_malloc(memory_region_length(REGION_SOUND1));
	for(i=0;i<memory_region_length(REGION_SOUND1);i++)samplebuf[i]=ROM[i]-0x80;
	return 0;
}
