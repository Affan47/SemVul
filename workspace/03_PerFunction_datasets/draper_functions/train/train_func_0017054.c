ref_sel(LINE_ID *id)
{
	ht_xex_shared_data *xex_shared=(ht_xex_shared_data *)format_group->get_shared_data();
	ht_format_viewer *hexv = find_hex_viewer(group);
	if (!hexv) return false;
	switch (id->id1) {
	case 0: {
		uint32 ofs = xex_shared->info_table_cooked[id->id2].start;
		uint32 size = xex_shared->info_table_cooked[id->id2].size;
		vstate_save();
		hexv->goto_offset(ofs, false);
		hexv->pselect_set(ofs, ofs+size);
		app->focus(hexv);
		return true;
	}
	case 1:
		switch (id->id2) {
		case 0: {
			vstate_save();
			uint32 ofs = xex_shared->header.file_header_offset;
			hexv->goto_offset(ofs, false);
			hexv->pselect_set(ofs, ofs+xex_shared->file_header.hdr_size);
			app->focus(hexv);
			return true;
		}
		case 1: {
			vstate_save();
			uint32 ofs = xex_shared->header.file_header_offset + 8;
			hexv->goto_offset(ofs, false);
			hexv->pselect_set(ofs, ofs+256);
			app->focus(hexv);
			return true;
		}
		}
	}
	return false;
}
