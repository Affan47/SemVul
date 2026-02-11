sidx_Read(GF_Box *s,GF_BitStream *bs)
{
	GF_Err e;
	u32 i;
	GF_SegmentIndexBox *ptr = (GF_SegmentIndexBox*) s;
	e = gf_isom_full_box_read(s, bs);
	if (e) return e;
	ptr->reference_ID = gf_bs_read_u32(bs);
	ptr->timescale = gf_bs_read_u32(bs);
	ptr->size -= 8;
	if (ptr->version==0) {
		ptr->earliest_presentation_time = gf_bs_read_u32(bs);
		ptr->first_offset = gf_bs_read_u32(bs);
		ptr->size -= 8;
	} else {
		ptr->earliest_presentation_time = gf_bs_read_u64(bs);
		ptr->first_offset = gf_bs_read_u64(bs);
		ptr->size -= 16;
	}
	gf_bs_read_u16(bs);
	ptr->nb_refs = gf_bs_read_u16(bs);
	ptr->size -= 4;
	ptr->refs = gf_malloc(sizeof(GF_SIDXReference)*ptr->nb_refs);
	for (i=0; i<ptr->nb_refs; i++) {
		ptr->refs[i].reference_type = gf_bs_read_int(bs, 1);
		ptr->refs[i].reference_size = gf_bs_read_int(bs, 31);
		ptr->refs[i].subsegment_duration = gf_bs_read_u32(bs);
		ptr->refs[i].starts_with_SAP = gf_bs_read_int(bs, 1);
		ptr->refs[i].SAP_type = gf_bs_read_int(bs, 3);
		ptr->refs[i].SAP_delta_time = gf_bs_read_int(bs, 28);
		ptr->size -= 12;
	}
	return GF_OK;
}
