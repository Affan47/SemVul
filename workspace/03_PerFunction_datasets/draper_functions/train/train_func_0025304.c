CalcPassageWeight ( const CSphVector<int> & dPassage, Passage_t & tPass, int iMaxWords, int iWordCountCoeff )
{
	DWORD uLast = 0;
	int iLCS = 1;
	tPass.m_iMaxLCS = 1;


	tPass.m_uWords = 0;
	tPass.m_iMinGap = iMaxWords-1;

	ARRAY_FOREACH ( i, dPassage )
	{
		Token_t & tTok = m_dTokens[dPassage[i]];
		assert ( tTok.m_eType==TOK_WORD );


		tPass.m_uWords |= tTok.m_uWords;


		uLast = tTok.m_uWords & ( uLast<<1 );
		if ( uLast )
		{
			iLCS++;
			tPass.m_iMaxLCS = Max ( iLCS, tPass.m_iMaxLCS );
		} else
		{
			iLCS = 1;
			uLast = tTok.m_uWords;
		}


		if ( tTok.m_uWords )
		{
			tPass.m_iMinGap = Min ( tPass.m_iMinGap, i );
			tPass.m_iMinGap = Min ( tPass.m_iMinGap, dPassage.GetLength()-1-i );
		}
	}
	assert ( tPass.m_iMinGap>=0 );


	tPass.m_iWordsWeight = 0;
	tPass.m_iWordCount = 0;

	DWORD uWords = tPass.m_uWords;
	for ( int iWord=0; uWords; uWords>>=1, iWord++ )
		if ( uWords & 1 )
	{
		tPass.m_iWordsWeight += m_dWords[iWord].m_iWeight;
		tPass.m_iWordCount++;
	}

	tPass.m_iMaxLCS *= iMaxWords;
	tPass.m_iWordCount *= iWordCountCoeff;
}
