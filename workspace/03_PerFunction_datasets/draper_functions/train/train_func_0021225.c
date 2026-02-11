WriteSchemaColumn ( CSphWriter & tWriter, const CSphColumnInfo & tColumn )
{
	int iLen = strlen ( tColumn.m_sName.cstr() );
	tWriter.PutDword ( iLen );
	tWriter.PutBytes ( tColumn.m_sName.cstr(), iLen );

	DWORD eAttrType = tColumn.m_eAttrType;
	if ( eAttrType==SPH_ATTR_WORDCOUNT )
		eAttrType = SPH_ATTR_INTEGER;
	tWriter.PutDword ( eAttrType );

	tWriter.PutDword ( tColumn.m_tLocator.CalcRowitem() );
	tWriter.PutDword ( tColumn.m_tLocator.m_iBitOffset );
	tWriter.PutDword ( tColumn.m_tLocator.m_iBitCount );

	tWriter.PutByte ( tColumn.m_bPayload );
}
