reread()
{
	lines->delAll();
	orig_lines->delAll();
	dirty = false;
	FileOfs ofs=0;
	int ll, pll=-1, ln=0;
	bool firstline = true;
	byte buf[TEXTFILE_MAX_LINELEN+1];

	lexer_state state=0;
	ht_ltextfile_line *e, *ce;

	if (lexer) state=lexer->getinitstate();

	uint l=0;
	while ((l=find_linelen_forwd(buf, sizeof buf, ofs, &ll))) {
		mFile->seek(ofs);
		uint x = mFile->read(buf, l-ll);
		buf[x]=0;

		e=new ht_ltextfile_line();
		e->is_in_memory=false;
		e->instate=state;
		e->on_disk.ofs=ofs;
		e->on_disk.len=l-ll;
		e->nofs=ofs;
		e->lineendlen=ll;
		assert( (uint)ll <= sizeof e->lineend);
		mFile->read(e->lineend, ll);
		lines->insert(e);
		ce=new ht_ltextfile_line();
		*ce = *e;
		orig_lines->insert(ce);

		if (lexer) {
			text_pos p;
			char *bufp=(char*)buf;
			uint toklen;
			bool start_of_line=true;
			p.line=ln;
			p.pofs=0;
			while (lexer->gettoken(bufp, l-ll-(bufp-(char*)buf), p, start_of_line, &state, &toklen)) {
				bufp+=toklen;
				p.pofs+=toklen;
				start_of_line=false;
			}
		}

		ofs+=l;
		pll=ll;
		firstline=false;
		ln++;
	}

	if (pll || firstline) {
		ll=0;
		e=new ht_ltextfile_line();
		e->is_in_memory=false;
		e->instate=state;
		e->on_disk.ofs=ofs;
		e->on_disk.len=l-ll;
		e->nofs=ofs;
		e->lineendlen=ll;
		lines->insert(e);
		ce=new ht_ltextfile_line();
		*ce = *e;
		orig_lines->insert(ce);
	}
}
