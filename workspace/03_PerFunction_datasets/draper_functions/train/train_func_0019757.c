CapWord()
{
	register int	num,
			restore = NO;
	Bufpos	b;

	DOTsave(&b);
	num = arg_value();
	if (num < 0) {
		restore = YES;
		f_word(num);
		num = -num;
	}
	while (num--) {
		to_word(FORWARD);
		if (eobp())
			break;

		if (upper(&linebuf[curchar])) {
			modify();
			makedirty(curline);
		}
		curchar += 1;
		while (!eolp() && jisword(linebuf[curchar])) {
			if (lower(&linebuf[curchar])) {
				modify();
				makedirty(curline);
			}
			curchar += 1;
		}
	}
	if (restore)
		SetDot(&b);
}
