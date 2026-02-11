stbl_GetSampleFragmentCount(GF_SampleFragmentBox *stsf, u32 sampleNumber)
{
	GF_StsfEntry *ent;
	u32 i, count;
	if (!stsf) return 0;


	if (!stsf->r_currentEntry || (stsf->r_currentEntry->SampleNumber < sampleNumber)) {
		stsf->r_currentEntry = NULL;
		stsf->r_currentEntryIndex = 0;
	}
	i = stsf->r_currentEntryIndex;

	count = gf_list_count(stsf->entryList);
	for (; i<count; i++) {
		ent = (GF_StsfEntry *)gf_list_get(stsf->entryList, i);
		if (ent->SampleNumber == sampleNumber) {
			stsf->r_currentEntry = ent;
			stsf->r_currentEntryIndex = i;
			return ent->fragmentCount;
		}
	}

	return 0;
}
