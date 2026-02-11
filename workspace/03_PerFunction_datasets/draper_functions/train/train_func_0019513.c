Perl__to_upper_title_latin1(pTHX_ const U8 c, U8* p, STRLEN *lenp, const char S_or_s)
{


    UV converted = toUPPER_LATIN1_MOD(c);

    PERL_ARGS_ASSERT__TO_UPPER_TITLE_LATIN1;

    assert(S_or_s == 'S' || S_or_s == 's');

    if (UNI_IS_INVARIANT(converted)) {

	*p = (U8) converted;
	*lenp = 1;
	return converted;
    }


    if (UNLIKELY(converted == LATIN_SMALL_LETTER_Y_WITH_DIAERESIS)) {
	switch (c) {
	    case LATIN_SMALL_LETTER_Y_WITH_DIAERESIS:
		converted = LATIN_CAPITAL_LETTER_Y_WITH_DIAERESIS;
		break;
	    case MICRO_SIGN:
		converted = GREEK_CAPITAL_LETTER_MU;
		break;
	    case LATIN_SMALL_LETTER_SHARP_S:
		*(p)++ = 'S';
		*p = S_or_s;
		*lenp = 2;
		return 'S';
	    default:
		Perl_croak(aTHX_ "panic: to_upper_title_latin1 did not expect '%c' to map to '%c'", c, LATIN_SMALL_LETTER_Y_WITH_DIAERESIS);
		assert(0);
	}
    }

    *(p)++ = UTF8_TWO_BYTE_HI(converted);
    *p = UTF8_TWO_BYTE_LO(converted);
    *lenp = 2;

    return converted;
}
