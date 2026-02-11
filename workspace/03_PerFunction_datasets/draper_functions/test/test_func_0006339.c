DebugGlyphAttributes()
{
	std::ofstream strmOut;
	strmOut.open("dbg_glyphattrs.txt");
	if (strmOut.fail())
	{
		g_errorList.AddError(6103, NULL,
			"Error in Griting to file ",
			"dbg_glyphattrs.txt");
		return;
	}

	Symbol psymBw = m_psymtbl->FindSymbol("breakweight");
	int nAttrIdBw = psymBw->InternalID();

	Symbol psymJStr = m_psymtbl->FindSymbol(GrcStructName("justify", "stretch"));
	int nAttrIdJStr = psymJStr->InternalID();

	if (g_errorList.AnyFatalErrors())
		strmOut << "Fatal errors--compilation aborted";
	else
	{
		strmOut << "GLYPH ATTRIBUTE IDS\n\n";
		for (size_t nAttrID = 0; nAttrID < m_vpsymGlyphAttrs.size(); nAttrID++)
		{
			if (m_vpsymGlyphAttrs[nAttrID]->InternalID() == static_cast<int>(nAttrID))
			{
				strmOut << nAttrID << ": "
					<< m_vpsymGlyphAttrs[nAttrID]->FullName() << "\n";
			}

		}
		strmOut << "\n\n\nGLYPH ATTRIBUTE VALUES\n\n";

		for (int wGlyphID = 0; wGlyphID < m_cwGlyphIDs; wGlyphID++)
		{

			ConvertBwForVersion(wGlyphID, nAttrIdBw);


			SplitLargeStretchValue(wGlyphID, nAttrIdJStr);

			bool fAnyNonZero = false;

			for (size_t nAttrID = 0; nAttrID < m_vpsymGlyphAttrs.size(); nAttrID++)
			{
				int nValue = FinalAttrValue(wGlyphID, nAttrID);


				if (nValue == 0)
					continue;

				if (fAnyNonZero == false)
				{
					strmOut << wGlyphID << "  [";
					DebugHex(strmOut, wGlyphID);
					strmOut << "]\n";
				}

				fAnyNonZero = true;

				strmOut << "   " << m_vpsymGlyphAttrs[nAttrID]->FullName()
					<< " = ";
				if (m_vpsymGlyphAttrs[nAttrID]->LastFieldIs("gpoint") &&
					nValue == kGpointZero)
				{
					strmOut << "zero" << "\n";
				}
				else
				{
					strmOut  << nValue;
					if (nValue > 9 || nValue < 0)
					{
						strmOut << " [";
						DebugHex(strmOut, nValue);
						strmOut << "]";
					}
					strmOut << "\n";
				}

			}

			if (fAnyNonZero)
				strmOut << "\n\n";
		}
	}

	strmOut.close();
}
