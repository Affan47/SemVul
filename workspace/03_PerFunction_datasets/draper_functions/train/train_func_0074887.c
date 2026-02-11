OnRedo ()
{
	if (m_RedoList.empty ())
		return false;
	xmlNodePtr node = m_RedoList.front ();
	gcp::TextObject *text = dynamic_cast <gcp::TextObject*> (m_Active->GetClient ());
	text->LoadSelected (node);
	m_RedoList.pop_front ();
	gcp::Window *pWin = static_cast < gcp::Window * > (m_pView->GetDoc ()->GetWindow ());
	if (m_RedoList.empty ())
		pWin->ActivateActionWidget ("/MainMenu/EditMenu/Redo", false);
	m_UndoList.push_front (m_CurNode);
	pWin->ActivateActionWidget ("/MainMenu/EditMenu/Undo", true);
	m_CurNode = node;
	return true;
}
