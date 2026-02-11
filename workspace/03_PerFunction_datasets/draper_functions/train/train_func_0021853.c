deco16_pf12_update(const data16_t *rowscroll_1_ptr, const data16_t *rowscroll_2_ptr)
{
	int bank1, bank2;


	deco16_pf_update(pf2_tilemap_8x8,pf2_tilemap_16x16,rowscroll_2_ptr,deco16_pf12_control[3], deco16_pf12_control[4], deco16_pf12_control[5]>>8, deco16_pf12_control[6]>>8);
	deco16_pf_update(pf1_tilemap_8x8,pf1_tilemap_16x16,rowscroll_1_ptr,deco16_pf12_control[1], deco16_pf12_control[2], deco16_pf12_control[5]&0xff, deco16_pf12_control[6]&0xff);


	if (deco16_bank_callback_1) {
		bank1=deco16_bank_callback_1(deco16_pf12_control[7]&0xff);
		if (bank1!=deco16_pf1_bank) {
			if (pf1_tilemap_8x8) tilemap_mark_all_tiles_dirty(pf1_tilemap_8x8);
			if (pf1_tilemap_16x16) tilemap_mark_all_tiles_dirty(pf1_tilemap_16x16);
		}

		deco16_pf1_bank=bank1;
	}

	if (deco16_bank_callback_2) {
		bank2=deco16_bank_callback_2(deco16_pf12_control[7]>>8);
		if (bank2!=deco16_pf2_bank) {
			if (pf2_tilemap_8x8) tilemap_mark_all_tiles_dirty(pf2_tilemap_8x8);
			if (pf2_tilemap_16x16) tilemap_mark_all_tiles_dirty(pf2_tilemap_16x16);
		}

		deco16_pf2_bank=bank2;
	}
}
