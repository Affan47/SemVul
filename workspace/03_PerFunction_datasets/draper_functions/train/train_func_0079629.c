MinimizeSchema ( CSphSchema & tDst, const CSphSchema & tSrc )
{

	if ( tDst.GetAttrsCount()==0 )
		return tSrc.GetAttrsCount()==0;


	CSphVector<CSphColumnInfo> dDst;
	for ( int i=0; i<tDst.GetAttrsCount(); i++ )
		dDst.Add ( tDst.GetAttr(i) );

	bool bEqual = ( tDst.GetAttrsCount()==tSrc.GetAttrsCount() );
	ARRAY_FOREACH ( i, dDst )
	{
		int iSrcIdx = tSrc.GetAttrIndex ( dDst[i].m_sName.cstr() );


		if ( iSrcIdx!=i )
			bEqual = false;


		if ( iSrcIdx>=0 )
		{
			const CSphColumnInfo & tSrcAttr = tSrc.GetAttr(iSrcIdx);
			if ( tSrcAttr.m_eAttrType!=dDst[i].m_eAttrType )
			{

				iSrcIdx = -1;
				bEqual = false;

			} else if ( tSrcAttr.m_tLocator.m_iBitCount!=dDst[i].m_tLocator.m_iBitCount )
			{

				dDst[i].m_tLocator.m_iBitCount = Max ( dDst[i].m_tLocator.m_iBitCount, tSrcAttr.m_tLocator.m_iBitCount );
				bEqual = false;
			}
		}


		if ( iSrcIdx<0 )
		{
			dDst.Remove ( i );
			i--;
		}
	}

	tDst.ResetAttrs ();
	ARRAY_FOREACH ( i, dDst )
		tDst.AddAttr ( dDst[i] );

	return bEqual;
}
