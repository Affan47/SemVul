defa_Size(GF_Box *s)
{
	GF_Err e;
	GF_UnknownBox *ptr = (GF_UnknownBox *)s;
	e = gf_isom_box_get_size(s);
	if (e) return e;
	ptr->size += ptr->dataSize;
	return GF_OK;
}
