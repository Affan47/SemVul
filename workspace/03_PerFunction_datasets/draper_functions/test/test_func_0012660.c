ParsePartyNumber(struct Aoc *chanp, u_char *p, u_char *end, char *str)
{
	INIT;

	XCHOICE_1(ParseNumberDigits, ASN1_TAG_NUMERIC_STRING, 0, str);
	XCHOICE_1(ParsePublicPartyNumber, ASN1_TAG_SEQUENCE, 1, str);
	XCHOICE_1(ParseNumberDigits, ASN1_TAG_NUMERIC_STRING, 3, str);
	XCHOICE_1(ParseNumberDigits, ASN1_TAG_NUMERIC_STRING, 4, str);
	XCHOICE_1(ParsePrivatePartyNumber, ASN1_TAG_SEQUENCE, 5, str);
	XCHOICE_1(ParseNumberDigits, ASN1_TAG_NUMERIC_STRING, 8, str);
	XCHOICE_DEFAULT;
}
