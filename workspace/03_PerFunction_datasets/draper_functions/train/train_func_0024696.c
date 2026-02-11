gf_tok_is_char_in_set(const char TestChar, const char *TestSet)
{
	u32 i, Len;
	Len = strlen(TestSet);
	for (i=0; i<Len; i++) {
		if (TestChar == TestSet[i]) return 1;
	}
	return 0;
}
