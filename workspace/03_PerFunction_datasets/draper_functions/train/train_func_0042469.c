esds_Size(GF_Box *s)
{
	GF_Err e;
	u32 descSize = 0;
	GF_ESDBox *ptr = (GF_ESDBox *)s;
	e = gf_isom_full_box_get_size(s);
	if (e) return e;
	descSize = gf_odf_desc_size((GF_Descriptor *)ptr->desc);
	ptr->size += descSize;
	return GF_OK;
}
