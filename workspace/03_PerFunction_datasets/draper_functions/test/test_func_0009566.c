meta_Write(GF_Box *s, GF_BitStream *bs)
{
	GF_Err e;
	GF_MetaBox *ptr = (GF_MetaBox *)s;
	if (!s) return GF_BAD_PARAM;
	e = gf_isom_full_box_write(s, bs);
	if (e) return e;
	if (ptr->handler) {
		e = gf_isom_box_write((GF_Box *) ptr->handler, bs);
		if (e) return e;
	}
	if (ptr->primary_resource) {
		e = gf_isom_box_write((GF_Box *) ptr->primary_resource, bs);
		if (e) return e;
	}
	if (ptr->file_locations) {
		e = gf_isom_box_write((GF_Box *) ptr->file_locations, bs);
		if (e) return e;
	}
	if (ptr->item_locations) {
		e = gf_isom_box_write((GF_Box *) ptr->item_locations, bs);
		if (e) return e;
	}
	if (ptr->protections) {
		e = gf_isom_box_write((GF_Box *) ptr->protections, bs);
		if (e) return e;
	}
	if (ptr->item_infos) {
		e = gf_isom_box_write((GF_Box *) ptr->item_infos, bs);
		if (e) return e;
	}
	if (ptr->IPMP_control) {
		e = gf_isom_box_write((GF_Box *) ptr->IPMP_control, bs);
		if (e) return e;
	}
	return GF_OK;
}
