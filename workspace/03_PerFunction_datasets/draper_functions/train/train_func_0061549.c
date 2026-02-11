ConfigureUnpack ( CSphVariant * pHead, ESphUnpackFormat eFormat, CSphSourceParams_SQL & tParams, const char * sSourceName )
{
	for ( CSphVariant * pVal = pHead; pVal; pVal = pVal->m_pNext )
	{
		CSphUnpackInfo & tUnpack = tParams.m_dUnpack.Add();
		tUnpack.m_sName = CSphString ( pVal->cstr() );
		tUnpack.m_eFormat = eFormat;
	}
	return true;
}
