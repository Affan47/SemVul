DebugFsm(GrcManager * pcman, std::ostream & strmOut)
{
	int nPassNum = PassDebuggerNumber();

	if (m_nGlobalID == -1)
	{
		strmOut << "\nPASS: " << nPassNum << "--no FSM\n";
		return;
	}


	strmOut << "\nPASS: " << nPassNum << "\n\nGlyph ID => Column:\n";

	int wFirst = 0;
	int wLast = 0;
	int ifsmcColCurr = -1;
	for (int w = 0; w < kMaxTotalGlyphs + 1; w++)
	{
		utf16 wTmp = w;
		char rgch[20];
		int ifsmcColumn;

		if (w == kMaxTotalGlyphs)
			ifsmcColumn = -1;
		else
		{

			std::map<utf16, int>::iterator hmit = m_hmGlyphToColumn.find(wTmp);
			if (hmit == m_hmGlyphToColumn.end())
				ifsmcColumn = -1;
			else
				ifsmcColumn = hmit->second;
		}
		if (ifsmcColCurr != ifsmcColumn)
		{

			if (ifsmcColCurr != -1)
			{
				wLast = w - 1;
				itoa(wFirst, rgch, 16);
				strmOut << "  0x";
				if (wFirst <= 0x0fff) strmOut << "0";
				if (wFirst <= 0x00ff) strmOut << "0";
				if (wFirst <= 0x000f) strmOut << "0";
				strmOut << rgch;
				if (wFirst < wLast)
				{
					itoa(wLast, rgch, 16);
					strmOut << "..0x";
					if (wLast <= 0x0fff) strmOut << "0";
					if (wLast <= 0x00ff) strmOut << "0";
					if (wLast <= 0x000f) strmOut << "0";
					strmOut << rgch;
				}
				else
					strmOut << "        ";


				strmOut << " => " << ifsmcColCurr << "\n";
			}

			ifsmcColCurr = ifsmcColumn;
			wFirst = w;
		}
	}


	strmOut << "\n";


	DebugFsmTable(pcman, strmOut, false);


	for (size_t irule = 0; irule < m_vprule.size(); irule++)
	{
		strmOut << "RULE " << nPassNum << "." << irule << ", ";
		m_vprule[irule]->LineAndFile().WriteToStream(strmOut, true);
		strmOut << ":  ";
		m_vprule[irule]->RulePrettyPrint(pcman, strmOut, false);
		strmOut << "\n\n";
	}
	strmOut << "\n";
}
