SelectionChanged (unsigned start, unsigned cur)
{
	if (start <= cur) {
		m_StartSel = start;
		m_EndSel = cur;
	} else {
		m_EndSel = start;
		m_StartSel = cur;
	}
	bool activate = m_EndSel > m_StartSel;
	Document* Doc = dynamic_cast<Document*> (GetDocument ());
	Window *Win = static_cast < Window * > (Doc->GetWindow ());
	Win->ActivateActionWidget ("/MainMenu/EditMenu/Erase", activate);
	Win->ActivateActionWidget ("/MainMenu/EditMenu/Copy", activate);
	Win->ActivateActionWidget ("/MainMenu/EditMenu/Cut", activate);
	if (m_Editor)
		m_Editor->SelectionChanged ();
}
