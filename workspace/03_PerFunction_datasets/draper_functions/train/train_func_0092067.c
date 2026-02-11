Move( int x, int y )
{
	bool bNeedRestore = m_IsVisible;
	if( m_IsVisible )
		Hide();
	m_Pos.x = x;	m_Pos.y = y;
	if( bNeedRestore )
		Show();
}
