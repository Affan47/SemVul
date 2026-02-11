gf_odf_new_smpte_camera()
{
	GF_SMPTECamera *newDesc = (GF_SMPTECamera *) gf_malloc(sizeof(GF_SMPTECamera));
	if (!newDesc) return NULL;

	newDesc->ParamList = gf_list_new();
	if (! newDesc->ParamList) {
		gf_free(newDesc);
		return NULL;
	}
	newDesc->cameraID = 0;
	newDesc->tag = GF_ODF_SMPTE_TAG;
	return (GF_Descriptor *) newDesc;
}
