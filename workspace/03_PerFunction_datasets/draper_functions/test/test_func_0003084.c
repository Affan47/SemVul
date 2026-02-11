Load_Blast_Surfaces(void)
{
	int i, j;
	char fpath[2048];

	for (i = 0; i < sizeof(Blastmap) / sizeof(Blastmap[0]); i++) {
		for (j = 0; j < Blastmap[i].phases; j++) {
			sprintf(fpath, "blasts/%s_%04d.png", Blastmap[i].name, j + 1);
			load_image(&Blastmap[i].images[j], fpath, TRUE);
		}
	}
}
