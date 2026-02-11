PostLookup(const void * pPost, size_t lPostSize, const void * pMaxp,
						const char * pPostName)
{
	using namespace Sfnt;

	const Sfnt::PostScriptGlyphName * pTable
		= reinterpret_cast<const Sfnt::PostScriptGlyphName *>(pPost);
	fixed format = read(pTable->format);

	if (format == PostScriptGlyphName::Format3)
	{
		return -2;
	}


	int iPostName = -1;
	for (int i = 0; i < kcPostNames; i++)
	{
		if (!strcmp(pPostName, rgPostName[i]))
		{
			iPostName = i;
			break;
		}
	}

	if (format == PostScriptGlyphName::Format1)
	{
		return iPostName;
	}

	if (format == PostScriptGlyphName::Format25)
	{
		if (iPostName == -1)
			return -1;

		const PostScriptGlyphName25 * pTable25
			= static_cast<const PostScriptGlyphName25 *>(pTable);
		int cnGlyphs = GlyphCount(pMaxp);
		for (gr::gid16 nGlyphId = 0; nGlyphId < cnGlyphs && nGlyphId < kcPostNames;
				nGlyphId++)
		{

			if (nGlyphId + pTable25->offset[nGlyphId] == iPostName)
				return nGlyphId;
		}
	}

	if (format == PostScriptGlyphName::Format2)
	{
		const PostScriptGlyphName2 * pTable2
			= static_cast<const PostScriptGlyphName2 *>(pTable);

		int cnGlyphs = read(pTable2->number_of_glyphs);

		if (iPostName != -1)
		{
			for (gr::gid16 nGlyphId = 0; nGlyphId < cnGlyphs; nGlyphId++)
			{
				if (read(pTable2->glyph_name_index[nGlyphId]) == iPostName)
					return nGlyphId;
			}
			return -1;
		}

		else
		{
			size_t nStrSizeGoal = strlen(pPostName);
			const char * pFirstGlyphName = reinterpret_cast<const char *>(
				&pTable2->glyph_name_index[0] + cnGlyphs);
			const char * pGlyphName = pFirstGlyphName;
			int iInNames = 0;
			bool fFound = false;
			const char * const endOfTable
				= reinterpret_cast<const char *>(pTable2) + lPostSize;
			while (pGlyphName < endOfTable && !fFound)
			{
				size_t nStringSize = size_t(*pGlyphName);
				if (nStrSizeGoal != nStringSize ||
					strncmp(pGlyphName + 1, pPostName, nStringSize))
				{
					++iInNames;
					pGlyphName += nStringSize + 1;
				}
				else
				{
					fFound = true;
				}
			}
			if (!fFound)
				return -1;

			iInNames += kcPostNames;
			for (gr::gid16 nGlyphId = 0; nGlyphId < cnGlyphs; nGlyphId++)
			{
				if (read(pTable2->glyph_name_index[nGlyphId]) == iInNames)
					return nGlyphId;
			}
			return -1;
		}
	}

	return -3;
}
