OnClicked ()
{
	int CurZ = m_pApp->GetCurZ ();
	if (m_pObject) {
		if (m_pObject->GetType () != AtomType)
			return false;
		if 	(((gcp::Atom*) m_pObject)->GetTotalBondsNumber () > (int) Element::GetMaxBonds (CurZ))
			return false;
		((gcp::Atom*) m_pObject)->GetCoords (&m_x0, &m_y0);
		m_x0 *= m_dZoomFactor;
		m_y0 *= m_dZoomFactor;
	}
	m_bChanged = true;
	gccv::Text *text = new gccv::Text (m_pView->GetCanvas (), m_x0, m_y0);
	m_Item = text;
	const gchar* symbol = gcu::Element::Symbol (CurZ);
	text->SetText (symbol);
	text->SetFontDescription (m_pView->GetPangoFontDesc ());
	text->SetPadding (m_pView->GetDoc ()->GetTheme ()->GetPadding ());
	text->SetFillColor (0);
	text->SetColor (gcp::AddColor);
	text->SetLineOffset (m_pView->GetCHeight ());
	text->GetPosition (m_x1, m_y1, m_x2, m_y2);
	m_x2 += m_x1;
	m_y2 += m_y1;
	return true;
}
