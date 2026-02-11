bms_make_singleton(int x)
{
	Bitmapset  *result;
	int			wordnum,
				bitnum;

	if (x < 0)
		elog(ERROR, "negative bitmapset member not allowed");
	wordnum = WORDNUM(x);
	bitnum = BITNUM(x);
	result = (Bitmapset *) palloc0(BITMAPSET_SIZE(wordnum + 1));
	result->nwords = wordnum + 1;
	result->words[wordnum] = ((bitmapword) 1 << bitnum);
	return result;
}
