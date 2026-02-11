parse_acc(char *p,
			struct abcsym *s)
{
	int pit, len, acc, nostem;
	unsigned nacc;

	if (s->u.key.nacc < 0) {
		syntax("'none' and explicit accidentals", 0);
		return p;
	}
	nacc = s->u.key.nacc;
	for (;;) {
		if (nacc >= sizeof s->u.key.pits) {
			syntax("Too many accidentals", 0);
			break;
		}
		p = parse_basic_note(p, &pit, &len, &acc, &nostem);
		s->u.key.pits[nacc] = pit - curvoice->add_pitch;
		s->u.key.accs[nacc++] = acc;
		if (*p == '\0')
			break;
		if (*p != '^' && *p != '_' && *p != '=')
			break;
	}
	s->u.key.nacc = nacc;
	return p;
}
