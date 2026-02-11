styl_Read(GF_Box *s, GF_BitStream *bs)
{
	u32 i;
	GF_TextStyleBox*ptr = (GF_TextStyleBox*)s;
	ptr->entry_count = gf_bs_read_u16(bs);
	if (ptr->entry_count) {
		ptr->styles = (GF_StyleRecord*)gf_malloc(sizeof(GF_StyleRecord)*ptr->entry_count);
		for (i=0; i<ptr->entry_count; i++) {
			gpp_read_style(bs, &ptr->styles[i]);
		}
	}
	return GF_OK;
}
