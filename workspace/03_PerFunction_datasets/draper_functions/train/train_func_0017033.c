button_press_event(GtkWidget * w, GdkEventButton * e)
{

	AP_UnixLeftRuler * pUnixLeftRuler = static_cast<AP_UnixLeftRuler *>(g_object_get_data(G_OBJECT(w), "user_data"));

	FV_View * pView = static_cast<FV_View *>(pUnixLeftRuler->m_pFrame->getCurrentView());
	if (!pView || pView->getPoint() == 0 || !pUnixLeftRuler->m_pG)
		return 1;


	gtk_grab_add(w);

	EV_EditModifierState ems = 0;
	EV_EditMouseButton emb = 0;

	if (e->state & GDK_SHIFT_MASK)
		ems |= EV_EMS_SHIFT;
	if (e->state & GDK_CONTROL_MASK)
		ems |= EV_EMS_CONTROL;
	if (e->state & GDK_MOD1_MASK)
		ems |= EV_EMS_ALT;

	if (e->state & GDK_BUTTON1_MASK)
		emb = EV_EMB_BUTTON1;
	else if (e->state & GDK_BUTTON2_MASK)
		emb = EV_EMB_BUTTON2;
	else if (e->state & GDK_BUTTON3_MASK)
		emb = EV_EMB_BUTTON3;

	pUnixLeftRuler->mousePress(ems, emb,
				   pUnixLeftRuler->m_pG->tlu(static_cast<UT_uint32>(e->x)),
				   pUnixLeftRuler->m_pG->tlu(static_cast<UT_uint32>(e->y)));

	return 1;
}
