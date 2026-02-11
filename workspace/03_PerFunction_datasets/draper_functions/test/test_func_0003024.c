NotifyFocus (bool has_focus, Target *target)
{
	if (target) {
		m_pActiveTarget = target;
		m_pActiveDoc = target->GetDocument ();
		m_pActiveTool->Activate ();
		if (has_focus)
			ShowTools (true);
	}
}
