gf_odf_del_oci_name(GF_OCICreators *ocn)
{
	u32 i;
	GF_OCICreator_item *tmp;
	if (!ocn) return GF_BAD_PARAM;

	i=0;
	while ((tmp = (GF_OCICreator_item *)gf_list_enum(ocn->OCICreators, &i))) {
		if (tmp->OCICreatorName) gf_free(tmp->OCICreatorName);
		gf_free(tmp);
	}
	gf_list_del(ocn->OCICreators);
	gf_free(ocn);
	return GF_OK;
}
