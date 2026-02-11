globexp2(const Char *ptr, const Char *pattern,
		    glob_t *pglob, int *rv)
{
	int     i;
	Char   *lm, *ls;
	const Char *pe, *pm, *pl;
	Char    patbuf[MaxPathLen + 1];


	for (lm = patbuf, pm = pattern; pm != ptr; *lm++ = *pm++)
		continue;
	ls = lm;


	for (i = 0, pe = ++ptr; *pe; pe++)
		if (*pe == CHAR_LBRACKET) {

			for (pm = pe++; *pe != CHAR_RBRACKET && *pe != CHAR_EOS; pe++)
				continue;
			if (*pe == CHAR_EOS) {


				pe = pm;
			}
		}
		else if (*pe == CHAR_LBRACE)
			i++;
		else if (*pe == CHAR_RBRACE) {
			if (i == 0)
				break;
			i--;
		}


	if (i != 0 || *pe == CHAR_EOS) {
		*rv = glob0(patbuf, pglob);
		return 0;
	}

	for (i = 0, pl = pm = ptr; pm <= pe; pm++)
		switch (*pm) {
		case CHAR_LBRACKET:

			for (pl = pm++; *pm != CHAR_RBRACKET && *pm != CHAR_EOS; pm++)
				continue;
			if (*pm == CHAR_EOS) {


				pm = pl;
			}
			break;

		case CHAR_LBRACE:
			i++;
			break;

		case CHAR_RBRACE:
			if (i) {
			    i--;
			    break;
			}

		case CHAR_COMMA:
			if (i && *pm == CHAR_COMMA)
				break;
			else {

				for (lm = ls; (pl < pm); *lm++ = *pl++)
					continue;


				for (pl = pe + 1; (*lm++ = *pl++) != CHAR_EOS;)
					continue;


#ifdef DEBUG
				qprintf("globexp2:", patbuf);
#endif
				*rv = globexp1(patbuf, pglob);


				pl = pm + 1;
			}
			break;

		default:
			break;
		}
	*rv = 0;
	return 0;
}
