gf_odf_new_kw()
{
	GF_KeyWord *newDesc = (GF_KeyWord *) gf_malloc(sizeof(GF_KeyWord));
	if (!newDesc) return NULL;

	newDesc->keyWordsList = gf_list_new();
	if (! newDesc->keyWordsList) {
		gf_free(newDesc);
		return NULL;
	}
	newDesc->isUTF8 = 0;
	newDesc->languageCode = 0;
	newDesc->tag = GF_ODF_KW_TAG;
	return (GF_Descriptor *) newDesc;
}
