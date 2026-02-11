OnRelease (double x, double y, unsigned int state)
{
	m_x = lastx = x;
	m_y = lasty = y;
	m_nState = state;
	m_bPressed = false;
	OnRelease ();
	m_pView->GetDoc ()->FinishOperation ();
	if (m_Item) {
		delete m_Item;
		m_Item = NULL;
	}
	m_pObject = NULL;
	m_pWidget = NULL;
	m_bChanged = false;
	m_pView->EnsureSize ();
}
