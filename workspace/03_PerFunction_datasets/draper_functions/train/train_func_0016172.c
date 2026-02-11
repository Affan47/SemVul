getLumps()
{
	size_t Offset = m_sOffset;
	m_pModel->m_Lumps.resize( kMaxLumps );
	for ( size_t idx=0; idx < kMaxLumps; idx++ )
	{
		sQ3BSPLump *pLump = new sQ3BSPLump;
		memcpy( pLump, &m_Data[ Offset ], sizeof( sQ3BSPLump ) );
		Offset += sizeof( sQ3BSPLump );
		m_pModel->m_Lumps[ idx ] = pLump;
	}
}
