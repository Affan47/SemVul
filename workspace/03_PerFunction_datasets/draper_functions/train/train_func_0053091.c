getline(uint line, uint pofs, void *buf, uint buflen, uint *retlen, lexer_state *state)
{


	ht_ltextfile_line *e=fetch_line(line);

	if (e) {
		if (is_dirty_parse(line)) update_parse(line);
		if (is_dirty_nofs(line)) update_nofs(line);


		uint ret;
		if (e->is_in_memory) {
			uint l=e->in_memory.len;
			if (l>buflen-1) l=buflen-1;
			if (pofs>l) l=0; else l-=pofs;
			memcpy(buf, e->in_memory.data+pofs, l);
			ret=l;
		} else {
			uint l=e->on_disk.len;
			if (l>buflen-1) l=buflen-1;
			if (pofs>l) l=0; else l-=pofs;
			mFile->seek(e->on_disk.ofs+pofs);
			mFile->read(buf, l);
			ret=l;
		}
		if (state) *state=e->instate;
		*retlen=ret;
		return true;
	}
	return false;
}
