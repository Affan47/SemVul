m4ds_Size(GF_Box *s)
{
	GF_Err e;
	u32 descSize;
	GF_MPEG4ExtensionDescriptorsBox *ptr = (GF_MPEG4ExtensionDescriptorsBox *)s;
	e = gf_isom_box_get_size(s);
	if (!e) e = gf_odf_desc_list_size(ptr->descriptors, &descSize);
	ptr->size += descSize;
	return e;
}
