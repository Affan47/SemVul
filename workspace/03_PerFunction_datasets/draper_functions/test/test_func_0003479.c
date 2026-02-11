CheckIndex ( const CSphIndex * pIndex, CSphString & sError )
{
	const CSphIndexSettings & tSettings = pIndex->GetSettings ();

	if ( ( tSettings.m_iMinPrefixLen>0 || tSettings.m_iMinInfixLen>0 ) && !pIndex->GetStar () )
	{
		CSphDict * pDict = pIndex->GetDictionary ();
		assert ( pDict );
		if ( pDict->GetSettings ().HasMorphology () )
		{
			sError = "infixes and morphology are enabled, enable_star=0";
			return false;
		}
	}

	return true;
}
