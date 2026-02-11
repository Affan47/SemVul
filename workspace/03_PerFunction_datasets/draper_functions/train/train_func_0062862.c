isearch_bw(const char *term, char **arg,
		      struct isearch_query *q)
{
	if (q->flags & ISEARCH_DSIZE) {
		printc_err("isearch: operand size already specified\n");
		return -1;
	}

	q->flags |= ISEARCH_DSIZE;
	switch (toupper(*term)) {
	case 'B':
		q->insn.dsize = MSP430_DSIZE_BYTE;
		break;

	case 'W':
		q->insn.dsize = MSP430_DSIZE_WORD;
		break;

	case 'A':
		q->insn.dsize = MSP430_DSIZE_AWORD;
		break;
	}

	return 0;
}
