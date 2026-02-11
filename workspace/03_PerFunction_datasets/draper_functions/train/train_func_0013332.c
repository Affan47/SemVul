GetStyleFirstWord(unsigned int szLine, Accessor &styler)
{
	int nsPos = styler.LineStart(szLine);
	int nePos = styler.LineStart(szLine+1) - 1;
	char ch = styler.SafeGetCharAt(nsPos);

	while (ch > 0 && isspacechar(ch) && nsPos < nePos)
	{
		nsPos++;
		ch = styler.SafeGetCharAt(nsPos);

	}
	return styler.StyleAt(nsPos);
}
