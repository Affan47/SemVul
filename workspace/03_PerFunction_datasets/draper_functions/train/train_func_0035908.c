gf_odf_new_esd_remove()
{
	GF_ESDRemove *newCom = (GF_ESDRemove *) gf_malloc(sizeof(GF_ESDRemove));
	if (!newCom) return NULL;
	newCom->NbESDs = 0;
	newCom->ES_ID = NULL;
	newCom->tag = GF_ODF_ESD_REMOVE_TAG;
	return (GF_ODCom *)newCom;
}
