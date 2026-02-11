GetStyleFirstWord(unsigned int szLine, Accessor &styler)
{
	int nsPos = styler.LineStart(szLine);
	int nePos = styler.LineStart(szLine+1) - 1;
	while (isspacechar(styler.SafeGetCharAt(nsPos)) && nsPos < nePos)
	{
		nsPos++;

	}
	return styler.StyleAt(nsPos);

}
