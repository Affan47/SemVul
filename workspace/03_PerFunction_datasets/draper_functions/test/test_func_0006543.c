get_inum_gen(const char *path, gfarm_ino_t *inump, gfarm_uint64_t *genp)
{
	unsigned int inum32, inum24, inum16, inum8, inum0;
	unsigned int gen32, gen0;
	gfarm_ino_t inum;
	gfarm_uint64_t gen;

	if (sscanf(path, "data/%08X/%02X/%02X/%02X/%02X%08X%08X",
		   &inum32, &inum24, &inum16, &inum8, &inum0, &gen32, &gen0)
	    != 7)
		return (-1);

	inum = ((gfarm_ino_t)inum32 << 32) + (inum24 << 24) +
		(inum16 << 16) + (inum8 << 8) + inum0;
	gen = ((gfarm_uint64_t)gen32 << 32) + gen0;
	*inump = inum;
	*genp = gen;

	return (0);
}
