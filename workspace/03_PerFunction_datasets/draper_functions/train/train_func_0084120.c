LoadHashSet()
{
	if (m_eStatus != AICH_HASHSETCOMPLETE) {
		wxFAIL;
		return false;
	}
	if ( !m_pHashTree.m_bHashValid || m_pHashTree.m_nDataSize != m_pOwner->GetFileSize() || m_pHashTree.m_nDataSize == 0) {
		wxFAIL;
		return false;
	}
	wxString fullpath = theApp->ConfigDir + KNOWN2_MET_FILENAME;
	CFile file(fullpath, CFile::read);
	if (!file.IsOpened()) {
		if (wxFileExists(fullpath)) {
			wxString strError(wxT("Failed to load ") KNOWN2_MET_FILENAME wxT(" file"));
			AddDebugLogLineC(logSHAHashSet, strError);
		}
		return false;
	}

	try {
		uint8 header = file.ReadUInt8();
		if (header != KNOWN2_MET_VERSION) {
			AddDebugLogLineC(logSHAHashSet, wxT("Loading failed: Current file is not a met-file!"));
			return false;
		}

		CAICHHash CurrentHash;
		uint64 nExistingSize = file.GetLength();
		uint32 nHashCount;
		while (file.GetPosition() < nExistingSize) {
			CurrentHash.Read(&file);
			if (m_pHashTree.m_Hash == CurrentHash) {

				uint32 nExpectedCount =	(PARTSIZE/EMBLOCKSIZE + ((PARTSIZE % EMBLOCKSIZE != 0)? 1 : 0)) * (m_pHashTree.m_nDataSize/PARTSIZE);
				if (m_pHashTree.m_nDataSize % PARTSIZE != 0) {
					nExpectedCount += (m_pHashTree.m_nDataSize % PARTSIZE)/EMBLOCKSIZE + (((m_pHashTree.m_nDataSize % PARTSIZE) % EMBLOCKSIZE != 0)? 1 : 0);
				}
				nHashCount = file.ReadUInt32();
				if (nHashCount != nExpectedCount) {
					AddDebugLogLineC(logSHAHashSet, wxT("Failed to load HashSet: Available Hashs and expected hashcount differ!"));
					return false;
				}
				if (!m_pHashTree.LoadLowestLevelHashs(&file)) {
					AddDebugLogLineC(logSHAHashSet, wxT("Failed to load HashSet: LoadLowestLevelHashs failed!"));
					return false;
				}
				if (!ReCalculateHash(false)) {
					AddDebugLogLineC(logSHAHashSet, wxT("Failed to load HashSet: Calculating loaded hashs failed!"));
					return false;
				}
				if (CurrentHash != m_pHashTree.m_Hash) {
					AddDebugLogLineC(logSHAHashSet, wxT("Failed to load HashSet: Calculated Masterhash differs from given Masterhash - hashset corrupt!"));
					return false;
				}
				return true;
			}
			nHashCount = file.ReadUInt32();
			if (file.GetPosition() + nHashCount*HASHSIZE > nExistingSize) {
				AddDebugLogLineC(logSHAHashSet, wxT("Saving failed: File contains fewer entries than specified!"));
				return false;
			}

			file.Seek(nHashCount*HASHSIZE, wxFromCurrent);
		}
		AddDebugLogLineC(logSHAHashSet, wxT("Failed to load HashSet: HashSet not found!"));
	} catch (const CSafeIOException& e) {
		AddDebugLogLineC(logSHAHashSet, wxT("IO error while loading AICH HashSet: ") + e.what());
	}

	return false;
}
