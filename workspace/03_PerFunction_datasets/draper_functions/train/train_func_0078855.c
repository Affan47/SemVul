cmph_config_set_hashfuncs(cmph_config_t *mph, CMPH_HASH *hashfuncs)
{
	switch (mph->algo)
	{
		case CMPH_CHM:
			chm_config_set_hashfuncs(mph, hashfuncs);
			break;
		case CMPH_BMZ:
			bmz_config_set_hashfuncs(mph, hashfuncs);
			break;
		case CMPH_BMZ8:
			bmz8_config_set_hashfuncs(mph, hashfuncs);
			break;
		case CMPH_BRZ:
			brz_config_set_hashfuncs(mph, hashfuncs);
			break;
		case CMPH_FCH:
			fch_config_set_hashfuncs(mph, hashfuncs);
			break;
		case CMPH_BDZ:
			bdz_config_set_hashfuncs(mph, hashfuncs);
			break;
		case CMPH_BDZ_PH:
			bdz_ph_config_set_hashfuncs(mph, hashfuncs);
			break;
		case CMPH_CHD_PH:
			chd_ph_config_set_hashfuncs(mph, hashfuncs);
			break;
		case CMPH_CHD:
			chd_config_set_hashfuncs(mph, hashfuncs);
			break;
		default:
			break;
	}
	return;
}
