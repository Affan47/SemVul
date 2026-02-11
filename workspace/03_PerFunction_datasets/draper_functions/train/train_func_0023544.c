utf8_to_utf32(const char *word8)
{
	UT_UCS4Char * ucs4 = 0;
	UT_UCS4_cloneString (&ucs4, UT_UCS4String (word8).ucs4_str());
	return ucs4;
}
