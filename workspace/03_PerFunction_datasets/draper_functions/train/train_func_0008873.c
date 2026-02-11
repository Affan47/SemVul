add_text(const char *str, int len)
{
	int new_alloc;
	char *new_text;

	if(len == 0)
		return;
	if(curdef_idx >= curdef_alloc || curdef_alloc - curdef_idx < len)
	{
		new_alloc = curdef_alloc + ((len + ALLOCBLOCKSIZE-1) & ~(ALLOCBLOCKSIZE-1));
		new_text = pp_xrealloc(curdef_text, new_alloc * sizeof(curdef_text[0]));
		if(!new_text)
			return;
		curdef_text = new_text;
		curdef_alloc = new_alloc;
		if(curdef_alloc > 65536)
			ppy_warning("Reallocating macro-expansion buffer larger than 64kB");
	}
	memcpy(&curdef_text[curdef_idx], str, len);
	curdef_idx += len;
}
