tx3g_Size(GF_Box *s)
{
	GF_Tx3gSampleEntryBox *ptr = (GF_Tx3gSampleEntryBox*)s;
	GF_Err e = gf_isom_box_get_size(s);
	if (e) return e;

	s->size += 18 + GPP_BOX_SIZE + GPP_STYLE_SIZE;
	if (ptr->font_table) {
		e = gf_isom_box_size((GF_Box *) ptr->font_table);
		if (e) return e;
		s->size += ptr->font_table->size;
	}
	return GF_OK;
}
