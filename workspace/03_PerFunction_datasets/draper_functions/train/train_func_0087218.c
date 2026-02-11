asrt_Read(GF_Box *s, GF_BitStream *bs)
{
	unsigned int i;
	GF_AdobeSegmentRunTableBox *ptr = (GF_AdobeSegmentRunTableBox *)s;

	GF_Err e = gf_isom_full_box_read(s, bs);
	if (e) return e;

	ptr->quality_entry_count = gf_bs_read_u8(bs);
	for (i=0; i<ptr->quality_entry_count; i++) {
		int j=0;
		u32 tmp_strsize=(u32)ptr->size-8;
		char *tmp_str = (char*) gf_malloc(tmp_strsize);
		while (tmp_strsize) {
			tmp_str[j] = gf_bs_read_u8(bs);
			tmp_strsize--;
			if (!tmp_str[j])
				break;
			j++;
		}
		gf_list_insert(ptr->quality_segment_url_modifiers, tmp_str, i);
	}

	ptr->segment_run_entry_count = gf_bs_read_u32(bs);
	for (i=0; i<ptr->segment_run_entry_count; i++) {
		GF_AdobeSegmentRunEntry *sre = gf_malloc(sizeof(GF_AdobeSegmentRunEntry));
		sre->first_segment = gf_bs_read_u32(bs);
		sre->fragment_per_segment = gf_bs_read_u32(bs);
		gf_list_insert(ptr->segment_run_entry_table, sre, i);
	}

	return GF_OK;
}
