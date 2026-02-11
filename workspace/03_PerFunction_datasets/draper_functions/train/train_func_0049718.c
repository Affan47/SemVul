ac3_Write(GF_Box *s, GF_BitStream *bs)
{
	GF_Err e;
	GF_AC3SampleEntryBox *ptr = (GF_AC3SampleEntryBox *)s;
	if (ptr->is_ec3) s->type = GF_ISOM_BOX_TYPE_EC3;
	e = gf_isom_box_write_header(s, bs);
	if (ptr->is_ec3) s->type = GF_ISOM_BOX_TYPE_AC3;
	if (e) return e;
	gf_isom_audio_sample_entry_write((GF_AudioSampleEntryBox*)s, bs);
	return gf_isom_box_write((GF_Box *)ptr->info, bs);
}
