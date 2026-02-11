elst_Read(GF_Box *s, GF_BitStream *bs)
{
	GF_Err e;
	u32 entries;
	s32 tr;
	u32 nb_entries;
	GF_EdtsEntry *p;
	GF_EditListBox *ptr = (GF_EditListBox *)s;

	e = gf_isom_full_box_read(s, bs);
	if (e) return e;
	nb_entries = gf_bs_read_u32(bs);

	for (entries = 0; entries < nb_entries; entries++ ) {
		p = (GF_EdtsEntry *) gf_malloc(sizeof(GF_EdtsEntry));
		if (!p) return GF_OUT_OF_MEM;
		if (ptr->version == 1) {
			p->segmentDuration = gf_bs_read_u64(bs);
			p->mediaTime = (s64) gf_bs_read_u64(bs);
		} else {
			p->segmentDuration = gf_bs_read_u32(bs);
			tr = gf_bs_read_u32(bs);
			p->mediaTime = (s64) tr;
		}
		p->mediaRate = gf_bs_read_u16(bs);
		gf_bs_read_u16(bs);
		gf_list_add(ptr->entryList, p);
	}
	return GF_OK;
}
