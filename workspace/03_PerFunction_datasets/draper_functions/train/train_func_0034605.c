cmph_load(FILE *f)
{
	cmph_t *mphf = NULL;
	DEBUGP("Loading mphf generic parts\n");
	mphf =  __cmph_load(f);
	if (mphf == NULL) return NULL;
	DEBUGP("Loading mphf algorithm dependent parts\n");

	switch (mphf->algo)
	{
		case CMPH_CHM:
			chm_load(f, mphf);
			break;
		case CMPH_BMZ:
			DEBUGP("Loading bmz algorithm dependent parts\n");
			bmz_load(f, mphf);
			break;
		case CMPH_BMZ8:
			DEBUGP("Loading bmz8 algorithm dependent parts\n");
			bmz8_load(f, mphf);
			break;
		case CMPH_BRZ:
			DEBUGP("Loading brz algorithm dependent parts\n");
			brz_load(f, mphf);
			break;
		case CMPH_FCH:
			DEBUGP("Loading fch algorithm dependent parts\n");
			fch_load(f, mphf);
			break;
		case CMPH_BDZ:
			DEBUGP("Loading bdz algorithm dependent parts\n");
			bdz_load(f, mphf);
			break;
		case CMPH_BDZ_PH:
			DEBUGP("Loading bdz_ph algorithm dependent parts\n");
			bdz_ph_load(f, mphf);
			break;
		case CMPH_CHD_PH:
			DEBUGP("Loading chd_ph algorithm dependent parts\n");
			chd_ph_load(f, mphf);
			break;
		case CMPH_CHD:
			DEBUGP("Loading chd algorithm dependent parts\n");
			chd_load(f, mphf);
			break;
		default:
			assert(0);
	}
	DEBUGP("Loaded mphf\n");
	return mphf;
}
