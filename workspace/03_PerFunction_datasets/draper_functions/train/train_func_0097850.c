OnButtonReleased (G_GNUC_UNUSED gccv::ItemClient *client, unsigned button, double x, double y, unsigned state)
{
	Application *App = m_pDoc->GetApplication ();
	Tool* pActiveTool = App? App->GetActiveTool (): NULL;
	if ((!m_pDoc->GetEditable ()) || (!pActiveTool))
		return true;
	switch (button) {
	case 1:
		if (!m_Dragging)
			break;
		m_Dragging = false;
		pActiveTool->OnRelease (x, y, state);
		if (!pActiveTool->GetOwnStatus ())
			m_pDoc->GetApplication ()->ClearStatus ();
		return true;
	}
	return true;
}
