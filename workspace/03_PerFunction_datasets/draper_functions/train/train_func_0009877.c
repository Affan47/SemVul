OnMouseMotion(wxMouseEvent &event)
{
	wxClientDC dc(this);
	m_barry_logo->HandleMotion(dc, event.m_x, event.m_y);


	if( m_current_mode )
		m_current_mode->OnMouseMotion(dc, event.m_x, event.m_y);
}
