dosearch(pattern, dir, re)
const char	*pattern;
int	dir;
bool	re;
{
	Bufpos	*pos;
	struct RE_block	re_blk;

	if (bobp() && eobp())
		return NULL;

	REcompile(pattern, re, &re_blk);

	pos = docompiled(dir, &re_blk);
	return pos;
}
