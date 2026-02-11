trun_Read(GF_Box *s, GF_BitStream *bs)
{
	GF_Err e;
	u32 i;
	GF_TrunEntry *p;
	GF_TrackFragmentRunBox *ptr = (GF_TrackFragmentRunBox *)s;

	e = gf_isom_full_box_read(s, bs);
	if (e) return e;


	if ((ptr->flags & GF_ISOM_TRUN_FIRST_FLAG) && (ptr->flags & GF_ISOM_TRUN_FLAGS))
		return GF_ISOM_INVALID_FILE;

	ptr->sample_count = gf_bs_read_u32(bs);


	if (ptr->flags & GF_ISOM_TRUN_DATA_OFFSET) {
		ptr->data_offset = gf_bs_read_u32(bs);
		ptr->size -= 4;
	}
	if (ptr->flags & GF_ISOM_TRUN_FIRST_FLAG) {
		ptr->first_sample_flags = gf_bs_read_u32(bs);
		ptr->size -= 4;
	}


	for (i=0; i<ptr->sample_count; i++) {
		u32 trun_size = 0;
		p = (GF_TrunEntry *) gf_malloc(sizeof(GF_TrunEntry));
		if (!p) return GF_OUT_OF_MEM;
		memset(p, 0, sizeof(GF_TrunEntry));

		if (ptr->flags & GF_ISOM_TRUN_DURATION) {
			p->Duration = gf_bs_read_u32(bs);
			trun_size += 4;
		}
		if (ptr->flags & GF_ISOM_TRUN_SIZE) {
			p->size = gf_bs_read_u32(bs);
			trun_size += 4;
		}

		if (ptr->flags & GF_ISOM_TRUN_FLAGS) {
			p->flags = gf_bs_read_u32(bs);
			trun_size += 4;
		}
		if (ptr->flags & GF_ISOM_TRUN_CTS_OFFSET) {
			p->CTS_Offset = gf_bs_read_u32(bs);
		}
		gf_list_add(ptr->entries, p);
		if (ptr->size<trun_size) return GF_ISOM_INVALID_FILE;
		ptr->size-=trun_size;
	}
	return GF_OK;
}
