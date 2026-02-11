SetHash(CFileDataIO* fileInput, uint32 wHashIdent, sint8 nLevel, bool bAllowOverwrite)
{
	if (nLevel == (-1)) {

		uint8 i = 0;
		for (; i != 32 && (wHashIdent & 0x80000000) == 0; ++i) {
			wHashIdent <<= 1;
		}
		if (i > 31) {
			AddDebugLogLineN(logSHAHashSet, wxT("CAICHHashTree::SetHash - found invalid HashIdent (0)"));
			return false;
		} else {
			nLevel = 31 - i;
		}
	}
	if (nLevel == 0) {

		if (m_bHashValid && !bAllowOverwrite) {

			CAICHHash(file);
			return true;
		}
		m_Hash.Read(fileInput);
		m_bHashValid = true;
		return true;
	} else if (m_nDataSize <= m_nBaseSize) {

		wxFAIL;
		return false;
	} else {

		wHashIdent <<= 1;
		nLevel--;
		uint64 nBlocks = m_nDataSize / m_nBaseSize + ((m_nDataSize % m_nBaseSize != 0 )? 1:0);
		uint64 nLeft = ( ((m_bIsLeftBranch) ? nBlocks+1:nBlocks) / 2)* m_nBaseSize;
		uint64 nRight = m_nDataSize - nLeft;
		if ((wHashIdent & 0x80000000) > 0) {
			if (m_pLeftTree == NULL) {
				m_pLeftTree = new CAICHHashTree(nLeft, true, (nLeft <= PARTSIZE) ? EMBLOCKSIZE : PARTSIZE);
			} else {
				wxASSERT( m_pLeftTree->m_nDataSize == nLeft );
			}
			return m_pLeftTree->SetHash(fileInput, wHashIdent, nLevel);
		} else {
			if (m_pRightTree == NULL) {
				m_pRightTree = new CAICHHashTree(nRight, false, (nRight <= PARTSIZE) ? EMBLOCKSIZE : PARTSIZE);
			} else {
				wxASSERT( m_pRightTree->m_nDataSize == nRight );
			}
			return m_pRightTree->SetHash(fileInput, wHashIdent, nLevel);
		}
	}
}
