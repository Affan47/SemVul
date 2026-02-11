getTotalMemory( void)
{
	FLMUINT	uiSize = sizeof( FlmRecord) +
							gv_FlmSysData.RCacheMgr.pRecBufAlloc->getTrueSize(
										m_uiBufferSize, m_pucBuffer);

	if (m_pucFieldIdTable)
	{
		uiSize += gv_FlmSysData.RCacheMgr.pRecBufAlloc->getTrueSize(
						fieldIdTableByteSize(), m_pucFieldIdTable);
	}
	return( uiSize);
}
