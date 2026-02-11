zCopySeedAlignment(zSeedAlignment *seed, zSeedAlignment *copy) {
	int i;
	copy->strand = seed->strand;
	copy->gb_start = seed->gb_start;
	copy->gb_end = seed->gb_end;
	copy->def  = zMalloc(sizeof(char)*(strlen(seed->def)+1), "zCopySeedAlignment: trellis->copy->def");
	strcpy(copy->def, seed->def);
	copy->hsps = seed->hsps;
	copy->hsp  = (zHSP*) zMalloc(copy->hsps*sizeof(zHSP), "zCopySeedAlignment: copy->hsp");
	for (i = 0; i < copy->hsps; i++) {
		zCopyHSP(&seed->hsp[i], &copy->hsp[i]);
	}
}
