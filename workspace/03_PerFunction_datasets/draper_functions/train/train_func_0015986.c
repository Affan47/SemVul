ghnt_New()
{
	GF_HintSampleEntryBox *tmp;
	GF_SAFEALLOC(tmp, GF_HintSampleEntryBox);
	if (tmp == NULL) return NULL;
	tmp->HintDataTable = gf_list_new();
	if (!tmp->HintDataTable) {
		gf_free(tmp);
		return NULL;
	}


	tmp->type = GF_ISOM_BOX_TYPE_GHNT;
	tmp->HintTrackVersion = 1;
	tmp->LastCompatibleVersion = 1;
	return (GF_Box *)tmp;
}
