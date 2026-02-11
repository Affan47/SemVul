OnLButtonUp(GdkEventButton* evt)
{
	if( !m_pTermData )
		return;
	ReleaseCapture();

	m_pTermData->m_Sel->Canonicalize();


	if( m_pTermData->m_Sel->Empty() )
	{
		int x = (int)evt->x;
		int y = (int)evt->y;
		PointToLineCol( &x, &y );

		int start, end;
                char buf[4096];
                if (HyperLinkHitTest(x, y, buf)) {
			char* pline = m_pTermData->m_Screen[y];
			OnHyperlinkClicked( string( (buf) ) );
		}
	}
	else
	{
		CopyToClipboard(true, false, false);
	}

}
