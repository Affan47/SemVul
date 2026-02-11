CheckRotate ()
{

	if ( !g_bDoRotate )
		return;


	if ( !g_bSeamlessRotate )
	{

		if ( g_iChildren )
			return;

		CSphConfigParser * pCP = NULL;

		if ( CheckConfigChanges () )
		{
			pCP = new CSphConfigParser;
			ReloadIndexSettings ( pCP );
		}

		g_hIndexes.IterateStart();
		while ( g_hIndexes.IterateNext() )
		{
			ServedIndex_t & tIndex = g_hIndexes.IterateGet();
			const char * sIndex = g_hIndexes.IterateGetKey().cstr();
			assert ( tIndex.m_pIndex );

			bool bWasAdded = tIndex.m_bOnlyNew;
			RotateIndexGreedy ( tIndex, sIndex );
			if ( bWasAdded && tIndex.m_bEnabled )
			{
				const CSphConfigType & hConf = pCP->m_tConf ["index"];
				if ( hConf.Exists ( sIndex ) )
				{
					CSphString sError;
					if ( !sphFixupIndexSettings ( tIndex.m_pIndex, hConf [sIndex], sError ) )
					{
						sphWarning ( "index '%s': %s - NOT SERVING", sIndex, sError.cstr() );
						tIndex.m_bEnabled = false;
					}

					if ( tIndex.m_bEnabled && !CheckIndex ( tIndex.m_pIndex, sError ) )
					{
						sphWarning ( "index '%s': %s - NOT SERVING", sIndex, sError.cstr() );
						tIndex.m_bEnabled = false;
					}
				}
			}
		}

		SafeDelete ( pCP );

		g_bDoRotate = false;
		sphInfo ( "rotating finished" );
		return;
	}


	assert ( g_bDoRotate && g_bSeamlessRotate );
	if ( g_dRotating.GetLength() || g_sPrereading )
		return;

	SafeDelete ( g_pCfg );
	if ( CheckConfigChanges () )
	{
		g_pCfg = new CSphConfigParser;
		ReloadIndexSettings ( g_pCfg );
	}


	g_hIndexes.IterateStart();
	while ( g_hIndexes.IterateNext() )
	{
		const ServedIndex_t & tIndex = g_hIndexes.IterateGet();
		const char * sIndex = g_hIndexes.IterateGetKey().cstr();
		assert ( tIndex.m_pIndex );

		CSphString sNewPath;
		sNewPath.SetSprintf ( "%s.new", tIndex.m_sIndexPath.cstr() );


		CSphString sTmp;
		sTmp.SetSprintf ( "%s.sph", sNewPath.cstr() );
		if ( !sphIsReadable ( sTmp.cstr() ) )
			continue;

		g_dRotating.Add ( sIndex );
	}

	SeamlessForkPrereader ();
}
