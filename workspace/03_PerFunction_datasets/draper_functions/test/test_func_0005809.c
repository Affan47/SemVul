update_parse(uint target)
{
	ht_ltextfile_line *e;
	uint line = first_parse_dirty_line;

	lexer_state instate=0;
	if (line) {
		instate = next_instate(line-1);


	} else {
		if (lexer) instate = lexer->getinitstate();
	}

	while (line<=target) {
		e = fetch_line(line);
		if (!e) break;

		e->instate = instate;
		first_parse_dirty_line = line+1;
		instate = next_instate(line);
		line++;
	}
	e = fetch_line(line);
	if (e) e->instate = instate;
}
