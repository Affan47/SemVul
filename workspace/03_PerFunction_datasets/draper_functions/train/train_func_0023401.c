DebugHex(std::ostream & strmOut, utf16 wGlyphID)
{
	char rgch[20];
	itoa(wGlyphID, rgch, 16);
	strmOut << "0x";
	if (wGlyphID <= 0x0fff) strmOut << "0";
	if (wGlyphID <= 0x00ff) strmOut << "0";
	if (wGlyphID <= 0x000f) strmOut << "0";
	strmOut << rgch;
}
