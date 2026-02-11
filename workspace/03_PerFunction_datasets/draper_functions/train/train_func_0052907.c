hthex_init(Bounds *b, File *file, ht_format_group *group)
{
	ht_hex_viewer *v = new ht_hex_viewer();
	v->init(b, DESC_HEX, VC_EDIT | VC_GOTO | VC_SEARCH | VC_REPLACE | VC_RESIZE, file, group);

	v->search_caps |= SEARCHMODE_BIN | SEARCHMODE_EVALSTR | SEARCHMODE_EXPR;

	v->h = new ht_hex_file_sub();
	v->h->init(file, 0, file->getSize(), 16, 0);

	v->insertsub(v->h);
	return v;
}
