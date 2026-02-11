WriteCmapItem(std::ofstream & strmOut,
	unsigned int nUnicode, bool fSuppPlaneChars, utf16 wGlyphID, bool fUnicodeToGlyph,
	bool fPseudo, bool fInCmap)
{
	if (fUnicodeToGlyph)
	{
		DebugUnicode(strmOut, nUnicode, fSuppPlaneChars);


		strmOut << "  => ";

		if (wGlyphID < 10)		strmOut << " ";
		if (wGlyphID < 100)		strmOut << " ";
		if (wGlyphID < 1000)	strmOut << " ";
		if (wGlyphID < 10000)	strmOut << " ";
		strmOut << wGlyphID << "  (";
		DebugHex(strmOut, wGlyphID);
		strmOut << ")";

		if (fPseudo)
		{
			if (fInCmap)
			{
				if (wGlyphID >= m_wFirstAutoPseudo)
					strmOut << "  [auto-pseudo]";
				else
					strmOut << "  [pseudo]";
			}
			else
				strmOut << "  [pseudo; not in cmap]";
		}

		strmOut << "\n";
	}
	else
	{
		strmOut << wGlyphID;
		if (wGlyphID < 10)		strmOut << " ";
		if (wGlyphID < 100)		strmOut << " ";
		if (wGlyphID < 1000)	strmOut << " ";
		if (wGlyphID < 10000)	strmOut << " ";
		strmOut << " =>  ";

		DebugUnicode(strmOut, nUnicode, fSuppPlaneChars);
		if (nUnicode < 0x0100)
			strmOut << "  '" << (char)nUnicode << "'";
		else
			strmOut << "     ";

		if (fPseudo)
		{
			if (fInCmap)
			{
				if (wGlyphID >= m_wFirstAutoPseudo)
					strmOut << "  [auto-pseudo]";
				else
					strmOut << "  [pseudo]";
			}
			else
				strmOut << "  [pseudo; not in cmap]";
		}

		strmOut << "\n";
	}
}
