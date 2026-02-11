init_ram_restrict(struct nvbios_init *init)
{


	if (!init->ramcfg || init->bios->version.major < 0x70)
		init->ramcfg = 0x80000000 | nvbios_ramcfg_index(init->subdev);
	return (init->ramcfg & 0x7fffffff);
}
