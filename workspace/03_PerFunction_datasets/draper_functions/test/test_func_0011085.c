unicode_grapheme_break(unicode_char a, unicode_char b)
{
	uint8_t ac=unicode_tab_lookup(a, unicode_indextab,
			 sizeof(unicode_indextab)/sizeof(unicode_indextab[0]),
			 unicode_rangetab,
			 unicode_classtab,
			 UNICODE_GRAPHEMEBREAK_ANY),
		bc=unicode_tab_lookup(b, unicode_indextab,
			 sizeof(unicode_indextab)/sizeof(unicode_indextab[0]),
			 unicode_rangetab,
			 unicode_classtab,
			 UNICODE_GRAPHEMEBREAK_ANY);


	if (ac == UNICODE_GRAPHEMEBREAK_CR && bc == UNICODE_GRAPHEMEBREAK_LF)
		return 0;


	switch (ac) {
	case UNICODE_GRAPHEMEBREAK_CR:
	case UNICODE_GRAPHEMEBREAK_LF:
	case UNICODE_GRAPHEMEBREAK_Control:
		return 1;
	default:
		break;
	}

	switch (bc) {
	case UNICODE_GRAPHEMEBREAK_CR:
	case UNICODE_GRAPHEMEBREAK_LF:
	case UNICODE_GRAPHEMEBREAK_Control:
		return 1;
	default:
		break;
	}

	if (ac == UNICODE_GRAPHEMEBREAK_L)
		switch (bc) {
		case UNICODE_GRAPHEMEBREAK_L:
		case UNICODE_GRAPHEMEBREAK_V:
		case UNICODE_GRAPHEMEBREAK_LV:
		case UNICODE_GRAPHEMEBREAK_LVT:
			return 0;
		}

	if ((ac == UNICODE_GRAPHEMEBREAK_LV ||
	     ac == UNICODE_GRAPHEMEBREAK_V) &&
	    (bc == UNICODE_GRAPHEMEBREAK_V ||
	     bc == UNICODE_GRAPHEMEBREAK_T))
		return 0;

	if ((ac == UNICODE_GRAPHEMEBREAK_LVT ||
	     ac == UNICODE_GRAPHEMEBREAK_T) &&
	    bc == UNICODE_GRAPHEMEBREAK_T)
		return 0;

	if (bc == UNICODE_GRAPHEMEBREAK_Extend)
		return 0;

	if (bc == UNICODE_GRAPHEMEBREAK_SpacingMark)
		return 0;

	if (ac == UNICODE_GRAPHEMEBREAK_Prepend)
		return 0;

	return 1;
}
