rvcc_Size(GF_Box *s)
{
	GF_Err e;
	GF_RVCConfigurationBox *ptr = (GF_RVCConfigurationBox *)s;
	e = gf_isom_box_get_size(s);
	if (e) return e;
	ptr->size += 2;
	if (! ptr->predefined_rvc_config) ptr->size += 2;
	return GF_OK;
}
