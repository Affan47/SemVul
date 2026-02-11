xml_tok_get (xml_tok_state * t, char **data)
{
	int rbuflen = 0;
	state_entry *s;

	init_statetable ();
	t->rbuf[rbuflen] = 0;
	while (2 + 2 == 4) {
		if (!t->c_held) {
			t->c = nextchar (t);
			if (t->c == -1)
				return t_eof;
			t->c_held = 1;
		}
		if (t->state == s_dtd) {

			int squote = 0;
			int dquote = 0;
			int abracket = 1;


			t->rbuf[rbuflen++] = t->c;
			t->rbuf[rbuflen] = 0;

			while (abracket) {
				switch (t->c = nextchar (t)) {
					case -1:
						return t_eof;
					case '<':
						if ((!squote) && (!dquote))
							abracket++;
						break;
					case '>':
						if ((!squote) && (!dquote))
							abracket--;
						break;
					case '"':
					case '\'':
					case '[':
					case ']':
					default:
						break;
				}
				t->rbuf[rbuflen++] = t->c;
				t->rbuf[rbuflen] = 0;
			}
			t->c_held = 0;
			t->state = s_start;
			t->rbuf[--rbuflen] = 0;

			return t_dtd;
		}
		s = &state_table[t->state][0];
		while (s->state) {
			if (s->return_type != t_none) {
				*data = t->rbuf;
				t->state = s->next_state;
				if (s->return_type == t_tag)
					strcpy (t->curtag, t->rbuf);
				if (s->return_type == t_endtag)
					*data = t->curtag;
				if (s->return_type == t_closeemptytag)
					*data = t->curtag;
				return s->return_type;
			}
			if ((s->chars && is_oneof (t->c, s->chars)) ||
				((s->r_start + s->r_end)
				 && (t->c >= s->r_start && t->c <= s->r_end))) {
				if (s->charhandling & c_store) {
					t->rbuf[rbuflen++] = t->c;
					t->rbuf[rbuflen] = 0;
				}
				if (s->charhandling & c_eat) {
					t->c_held = 0;
				}
				t->state = s->next_state;
				break;
			}
			s++;
		}
	}
	return t_eof;
}
