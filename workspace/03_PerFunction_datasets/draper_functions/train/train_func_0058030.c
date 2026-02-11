button_release_event(GtkWidget * w, GdkEventButton * e)
{

	AP_UnixTopRuler * pUnixTopRuler = static_cast<AP_UnixTopRuler *>(g_object_get_data(G_OBJECT(w), "user_data"));

	EV_EditModifierState ems = 0;
	EV_EditMouseButton emb = 0;

	if (!pUnixTopRuler->getGraphics())
		return 1;

	if (e->state & GDK_SHIFT_MASK)
		ems |= EV_EMS_SHIFT;
	if (e->state & GDK_CONTROL_MASK)
		ems |= EV_EMS_CONTROL;
	if (e->state & GDK_MOD1_MASK)
		ems |= EV_EMS_ALT;

	if (1 == e->button )
		emb = EV_EMB_BUTTON1;
	else if (2 == e->button )
		emb = EV_EMB_BUTTON2;
	else if (3 == e->button)
		emb = EV_EMB_BUTTON3;

	pUnixTopRuler->mouseRelease(ems, emb,
				  pUnixTopRuler->getGraphics()->tlu(static_cast<UT_uint32>(e->x)),
				  pUnixTopRuler->getGraphics()->tlu(static_cast<UT_uint32>(e->y)));


	gtk_grab_remove(w);

	return 1;
}
