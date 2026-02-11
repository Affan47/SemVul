OnPaint(wxPaintEvent& event)
{
	wxRect rect = GetClientRect();
	wxPaintDC dc(this);
	dc.SetPen(*wxBLACK_PEN);
	dc.SetTextForeground(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

#ifdef __WXMSW__
	dc.DrawLine(rect.GetLeft(), rect.GetBottom(), m_cbOffset, rect.GetBottom());
#else
	dc.DrawLine(rect.GetLeft(), rect.GetBottom(), rect.GetRight(), rect.GetBottom());
#endif
}
