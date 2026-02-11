DetectIpAddrs()
{
	int iline = m_FirstLine;
	int ilast_line = iline + m_RowsPerPage;
	for( ; iline < ilast_line; iline++ )
	{
		char* line = m_Screen[iline];
		CTermCharAttr* attr = GetLineAttr( line );

		for( int col = 0; col < m_ColsPerPage; col ++ )
			attr[col].SetIpAddr(false);
		DetectIpPatterns( line, attr, m_ColsPerPage, &m_RegIp );
	}
}
