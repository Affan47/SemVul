schi_Size(GF_Box *s)
{
	GF_Err e;
	GF_SchemeInformationBox *ptr = (GF_SchemeInformationBox *)s;
	if (!s) return GF_BAD_PARAM;
	e = gf_isom_box_get_size(s);
	if (e) return e;

	if (ptr->ikms) {
		e = gf_isom_box_size((GF_Box *) ptr->ikms);
		if (e) return e;
		ptr->size += ptr->ikms->size;
	}
	if (ptr->isfm) {
		e = gf_isom_box_size((GF_Box *) ptr->isfm);
		if (e) return e;
		ptr->size += ptr->isfm->size;
	}
	if (ptr->okms) {
		e = gf_isom_box_size((GF_Box *) ptr->okms);
		if (e) return e;
		ptr->size += ptr->okms->size;
	}
	if (ptr->tenc) {
		e = gf_isom_box_size((GF_Box *) ptr->tenc);
		if (e) return e;
		ptr->size += ptr->tenc->size;
	}
	if (ptr->piff_tenc) {
		e = gf_isom_box_size((GF_Box *) ptr->tenc);
		if (e) return e;
		ptr->size += ptr->tenc->size;
	}
	return GF_OK;
}
