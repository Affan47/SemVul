skip_uri(str* _s)
{
	register int st = ST1;

	while(_s->len) {
		switch(*(_s->s)) {
		case ',':
		case ';':
			if (st == ST1) return 0;
			break;

		case '\"':
			switch(st) {
			case ST1: st = ST2; break;
			case ST2: st = ST1; break;
			case ST3: st = ST4; break;
			case ST4: st = ST3; break;
			case ST5: st = ST2; break;
			case ST6: st = ST4; break;
			}
			break;

		case '<':
			switch(st) {
			case ST1: st = ST3; break;
			case ST3:
				LM_ERR("second < found\n");
				return -1;
			case ST5: st = ST2; break;
			case ST6: st = ST4; break;
			}
			break;

		case '>':
			switch(st) {
			case ST1:
				LM_ERR("> is first\n");
				return -2;

			case ST3: st = ST1; break;
			case ST5: st = ST2; break;
			case ST6: st = ST4; break;
			}
			break;

		case '\\':
			switch(st) {
			case ST2: st = ST5; break;
			case ST4: st = ST6; break;
			case ST5: st = ST2; break;
			case ST6: st = ST4; break;
			}
			break;

		default: break;

		}

		_s->s++;
		_s->len--;
	}

	if (st != ST1) {
		LM_ERR("< or \" not closed\n");
		return -3;
	}

	return 0;
}
