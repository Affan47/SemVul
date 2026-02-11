assign(const char *s)
{
	int slen = s ? strlen(s) : 0;
	realloc(slen);
	memcpy(mContent, s, mLength);
}
