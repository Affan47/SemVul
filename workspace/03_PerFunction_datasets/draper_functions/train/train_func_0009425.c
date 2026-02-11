breakText(const core::stringw& text, core::stringw& brokenText, u32 cellWidth)
{
	IGUISkin* skin = Environment->getSkin();

	if (!skin)
		return;

	if (!Font)
		return;

	IGUIFont* font = skin->getFont();
	if (!font)
		return;

	core::stringw line, lineDots;
	wchar_t c[2];
	c[1] = L'\0';

	const u32 maxLength = cellWidth - (CellWidthPadding * 2);
	const u32 maxLengthDots = cellWidth - (CellWidthPadding * 2) - font->getDimension(L"...").Width;
	const u32 size = text.size();
	u32 pos = 0;

	u32 i;

	for (i=0; i<size; ++i)
	{
		c[0] = text[i];

		if (c[0] == L'\n')
			break;

		pos += font->getDimension(c).Width;
		if ( pos > maxLength )
			break;

		if ( font->getDimension( (line + c).c_str() ).Width > maxLengthDots )
			lineDots = line;

		line += c[0];
	}

	if ( i < size )
		brokenText = lineDots + L"...";
	else
		brokenText = line;
}
