offset_to_pos(FileOfs ofs, viewer_pos *p)
{
	uint ll = h->get_line_length();
	uint disp = h->get_disp();
	clear_viewer_pos(p);
	p->u.sub = first_sub;
	FileOfs id;
	if (ofs < disp) {
		id = 0;
		p->u.tag_idx = ofs;
	} else {
		id = ofs - ((ofs - disp) % ll);
		p->u.tag_idx = (ofs - disp) % ll;
	}
	p->u.line_id.id1 = id >> 32;
	p->u.line_id.id2 = id;
	return true;
}
