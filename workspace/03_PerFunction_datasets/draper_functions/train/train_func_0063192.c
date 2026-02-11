Show(bool bImmediately)
{
	m_IsVisible = true;
	if( bImmediately && !m_IsShow ){
		m_IsShow = true;
		DrawInverse();
	}
}
