AssignGlyphIDToMachineClasses(utf16 wGlyphID, int nPassID)
{
	SourceClassSet * pscsThisGlyph = m_rgscsInclusions + wGlyphID;
	if (pscsThisGlyph->size() == 0)


		return -1;


	int nKey = MachineClassKey(wGlyphID, nPassID);

	std::vector<FsmMachineClass *> * pvpfsmc;
	FsmMachineClass * pfsmc;
	std::map<int, MachineClassList>::iterator hmit = m_hmMachineClassMap.find(nKey);
	if (hmit == m_hmMachineClassMap.end())
	{


		pfsmc = new FsmMachineClass(nPassID);
		pfsmc->SetColumn(m_vpfsmc.size());
		pfsmc->AddGlyph(wGlyphID);
		pfsmc->SetSourceClasses(pscsThisGlyph);


		m_vpfsmc.push_back(pfsmc);


		pvpfsmc = new std::vector<FsmMachineClass *>;
		pvpfsmc->push_back(pfsmc);
		std::pair<int, MachineClassList> hmPair;
		hmPair.first = nKey;
		hmPair.second = pvpfsmc;
		m_hmMachineClassMap.insert(hmPair);

	}
	else

	{


		pvpfsmc = hmit->second;
		pfsmc = MachineClassMatching(*pvpfsmc, wGlyphID);
		if (pfsmc)
		{

			pfsmc->AddGlyph(wGlyphID);
		}
		else
		{


			pfsmc = new FsmMachineClass(nPassID);
			pfsmc->SetColumn(m_vpfsmc.size());
			pfsmc->AddGlyph(wGlyphID);
			pfsmc->SetSourceClasses(pscsThisGlyph);


			m_vpfsmc.push_back(pfsmc);


			pvpfsmc->push_back(pfsmc);
		}
	}


	m_rgpfsmcAssignments[wGlyphID] = pfsmc;
	return pfsmc->Column();
}
