GetKeywords ( CSphVector<CSphKeywordInfo> & dKeywords, const char * sQuery, bool bGetStats, CSphString & sError ) const
{
	m_tRwlock.ReadLock();

	RtQword_t tQword;
	CSphString sBuffer ( sQuery );

	CSphScopedPtr<ISphTokenizer> pTokenizer ( m_pTokenizer->Clone ( false ) );
	pTokenizer->SetBuffer ( (BYTE *)sBuffer.cstr(), sBuffer.Length() );

	while ( BYTE * pToken = pTokenizer->GetToken() )
	{
		const char * sToken = (const char *)pToken;
		CSphString sWord ( sToken );
		SphWordID_t iWord = m_pDict->GetWordID ( pToken );
		if ( iWord )
		{
			CSphKeywordInfo & tInfo = dKeywords.Add();
			tInfo.m_sTokenized = sWord;
			tInfo.m_sNormalized = sToken;
			tInfo.m_iDocs = 0;
			tInfo.m_iHits = 0;

			if ( !bGetStats )
				continue;

			tQword.m_iWordID = iWord;
			tQword.m_iDocs = 0;
			tQword.m_iHits = 0;
			ARRAY_FOREACH ( iSeg, m_pSegments )
				RtQwordSetupSegment ( &tQword, m_pSegments[iSeg], false );

			tInfo.m_iDocs = tQword.m_iDocs;
			tInfo.m_iHits = tQword.m_iHits;
		}
	}


	if ( bGetStats )
		ARRAY_FOREACH ( iChunk, m_pDiskChunks )
	{
		CSphVector<CSphKeywordInfo> dKeywords2;
		if ( !m_pDiskChunks[iChunk]->GetKeywords ( dKeywords2, sQuery, bGetStats, sError ) )
		{
			m_tRwlock.Unlock();
			return false;
		}

		if ( dKeywords.GetLength()!=dKeywords2.GetLength() )
		{
			sError.SetSprintf ( "INTERNAL ERROR: keyword count mismatch (ram=%d, disk[%d]=%d)",
				dKeywords.GetLength(), iChunk, dKeywords2.GetLength() );
			m_tRwlock.Unlock ();
			break;
		}

		ARRAY_FOREACH ( i, dKeywords )
		{
			if ( dKeywords[i].m_sTokenized!=dKeywords2[i].m_sTokenized )
			{
				sError.SetSprintf ( "INTERNAL ERROR: tokenized keyword mismatch (n=%d, ram=%s, disk[%d]=%s)",
					i, dKeywords[i].m_sTokenized.cstr(), iChunk, dKeywords2[i].m_sTokenized.cstr() );
				m_tRwlock.Unlock ();
				break;
			}

			if ( dKeywords[i].m_sNormalized!=dKeywords2[i].m_sNormalized )
			{
				sError.SetSprintf ( "INTERNAL ERROR: normalized keyword mismatch (n=%d, ram=%s, disk[%d]=%s)",
					i, dKeywords[i].m_sTokenized.cstr(), iChunk, dKeywords2[i].m_sTokenized.cstr() );
				m_tRwlock.Unlock ();
				break;
			}

			dKeywords[i].m_iDocs += dKeywords2[i].m_iDocs;
			dKeywords[i].m_iHits += dKeywords2[i].m_iHits;
		}
	}

	m_tRwlock.Unlock();
	return true;
}
