regatom(flagp)
int *flagp;
{
	register char *ret;
	int flags;

	*flagp = WORST;

	switch (*regparse++) {
	case '^':
		ret = regnode(BOL);
		break;
	case '$':
		ret = regnode(EOL);
		break;
	case '.':
		ret = regnode(ANY);
		*flagp |= HASWIDTH|SIMPLE;
		break;
	case '[': {
			register int class;
			register int classend;

			if (*regparse == '^') {
				ret = regnode(ANYBUT);
				regparse++;
			} else
				ret = regnode(ANYOF);
			if (*regparse == ']' || *regparse == '-')
				regc(*regparse++);
			while (*regparse != '\0' && *regparse != ']') {
				if (*regparse == '-') {
					regparse++;
					if (*regparse == ']' || *regparse == '\0')
						regc('-');
					else {
						class = UCHARAT(regparse-2)+1;
						classend = UCHARAT(regparse);
						if (class > classend+1)
							FAIL("invalid [] range");
						for (; class <= classend; class++)
							regc(class);
						regparse++;
					}
				} else
					regc(*regparse++);
			}
			regc('\0');
			if (*regparse != ']')
				FAIL("unmatched []");
			regparse++;
			*flagp |= HASWIDTH|SIMPLE;
		}
		break;
	case '(':
		ret = reg(1, &flags);
		if (ret == NULL)
			return(NULL);
		*flagp |= flags&(HASWIDTH|SPSTART);
		break;
	case '\0':
	case '|':
	case ')':
		FAIL("internal urp");
		break;
	case '?':
	case '+':
	case '*':
		FAIL("?+* follows nothing");
		break;
	case '\\':
		if (*regparse == '\0')
			FAIL("trailing \\");
		ret = regnode(EXACTLY);
		regc(*regparse++);
		regc('\0');
		*flagp |= HASWIDTH|SIMPLE;
		break;
	default: {
			register int len;
			register char ender;

			regparse--;
			len = strcspn(regparse, META);
			if (len <= 0)
				FAIL("internal disaster");
			ender = *(regparse+len);
			if (len > 1 && ISMULT(ender))
				len--;
			*flagp |= HASWIDTH;
			if (len == 1)
				*flagp |= SIMPLE;
			ret = regnode(EXACTLY);
			while (len > 0) {
				regc(*regparse++);
				len--;
			}
			regc('\0');
		}
		break;
	}

	return(ret);
}
