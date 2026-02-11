OnFlip (bool horizontal)
{
	if (!m_pData) {
		m_pView = m_pApp->GetActiveDocument ()->GetView ();
		GtkWidget *w = m_pView->GetWidget ();
		m_pData = (gcp::WidgetData*) g_object_get_data (G_OBJECT (w), "data");
	}
	if (!m_pData->SelectedObjects.size ())
		return;
	gccv::Rect rect;
	m_pData->GetSelectionBounds (rect);
	m_cx = (rect.x0 + rect.x1) / 2.;
	m_cy = (rect.y0 + rect.y1) / 2.;
	m_x = (horizontal)? -1.: 1.;
	Matrix2D m(m_x, 0., 0., -m_x);
	std::set < Object * >::iterator i, end = m_pData->SelectedObjects.end ();
	gcp::Document* pDoc = m_pView->GetDoc ();
	gcp::Theme *pTheme = pDoc->GetTheme ();
	m_pOp = pDoc-> GetNewOperation (gcp::GCP_MODIFY_OPERATION);
	for (i = m_pData->SelectedObjects.begin (); i != end; i++) {
		m_pOp->AddObject (*i,0);
		(*i)->Transform2D (m, m_cx / pTheme->GetZoomFactor (), m_cy / pTheme->GetZoomFactor ());
		m_pView->Update (*i);
		m_pOp->AddObject (*i,1);
	}
	pDoc->FinishOperation ();
}
