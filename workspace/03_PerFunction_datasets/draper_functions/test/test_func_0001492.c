next_char(pCPP_ struct lexer_state *ls)
{
	int c;

	if (!ls->discard) return ls->last;
	ls->discard = 0;
	do {
		c = next_fifo_char(ls);

		if (c == '?' && char_lka1(ls) == '?'
			&& (ls->flags & HANDLE_TRIGRAPHS)) {
			int i, d;

			d = char_lka2(aCPP_ ls);
			for (i = 0; i < 9; i ++) if (d == trig[i].old) {
				if (ls->flags & WARN_TRIGRAPHS) {
					ls->count_trigraphs ++;
				}
				if (ls->flags & WARN_TRIGRAPHS_MORE) {
					warning(aCPP_ ls->line, "trigraph ?""?%c "
						"encountered", d);
				}
				next_fifo_char(ls);
				next_fifo_char(ls);
				c = trig[i].new;
				break;
			}
		}
		if (c == '\\' && char_lka1(ls) == '\n') {
			ls->line ++;
			next_fifo_char(ls);
		} else {
			ls->last = c;
			return c;
		}
	} while (1);
}
