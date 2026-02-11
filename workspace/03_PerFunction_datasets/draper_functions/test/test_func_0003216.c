IsDeepComposite(gr::gid16 nGlyphId, const void * pGlyf, const void * pLoca,
							 long lLocaSize, const void * pHead)
{
	if (IsSpace(nGlyphId, pLoca, lLocaSize, pHead)) {return false;}

	void * pSimpleGlyf = GlyfLookup(nGlyphId, pGlyf, pLoca, lLocaSize, pHead);
	if (pSimpleGlyf == NULL)
		return false;

	if (GlyfContourCount(pSimpleGlyf) >= 0)
		return false;

	int rgnCompId[kMaxGlyphComponents];
	size_t cCompIdTotal = kMaxGlyphComponents;
	size_t cCompId = 0;

	if (!GetComponentGlyphIds(pSimpleGlyf, rgnCompId, cCompIdTotal, cCompId))
		return false;

	for (size_t i = 0; i < cCompId; i++)
	{
		pSimpleGlyf = GlyfLookup(static_cast<gr::gid16>(rgnCompId[i]),
										pGlyf, pLoca, lLocaSize, pHead);
		if (pSimpleGlyf == NULL) {return false;}

		if (GlyfContourCount(pSimpleGlyf) < 0)
			return true;
	}

	return false;
}
