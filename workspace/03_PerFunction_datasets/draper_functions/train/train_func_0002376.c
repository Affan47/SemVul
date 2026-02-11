htlepagemaps_init(Bounds *b, File *file, ht_format_group *group)
{
	ht_le_shared_data *le_shared=(ht_le_shared_data *)group->get_shared_data();

	FileOfs h = le_shared->hdr_ofs;
	ht_uformat_viewer *v=new ht_uformat_viewer();
	v->init(b, DESC_LE_PAGEMAP, VC_EDIT | VC_SEARCH, file, group);

	ht_mask_sub *m = new ht_mask_sub();
	m->init(file, 0);

	char t[64];
	ht_snprintf(t, sizeof t, "* LE page maps at offset %08qx", h+le_shared->hdr.pagemap);
	m->add_mask(t);

	v->insertsub(m);


	bool le_bigendian = false;

	for (uint32 i=0; i<le_shared->hdr.pagecnt; i++) {
		m=new ht_mask_sub();
		m->init(file, i);

		ht_snprintf(t, sizeof t, "--- page %d at %08x ---", i+1, le_shared->pagemap.offset[i]);
		m->add_staticmask_ptable(lepagemap, h+le_shared->hdr.pagemap+i*4, le_bigendian);
		ht_collapsable_sub *cs=new ht_collapsable_sub();
		cs->init(file, m, 1, t, 1);
		v->insertsub(cs);
	}

	le_shared->v_pagemaps=v;
	return v;
}
