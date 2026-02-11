CalcShareSize()
{
	CString s,s1;
	CDir dir;
	ulonglong iSSize;

	iSSize = 0;
	m_pShareFolder=0;

	if ( CConfig::Instance()->GetSharedFolders(&m_SharedFolders) == 0 )
	{
		printf("No share folderfound !");
		return 0;
	}

	while ( (m_pShareFolder=m_SharedFolders.Next(m_pShareFolder)) != 0 )
	{

		s = m_pShareFolder->m_sPath;


		if ( dir.cd(s) )
		{
			s  = dir.Path();
			s1 = dir.DirName();

			if ( s1.NotEmpty() )
			{
				s = s.Left( s.Length()-s1.Length() );
			}

			iSSize += CalcShareSize( 0, s, s1, CString() );
		}
		else
		{
			printf("Can't change to dir: '%s'\n",s.Data());
		}
	}

	return iSSize;
}
