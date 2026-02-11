key_press_event(GtkWidget* w, GdkEventKey* e)
{
	XAP_UnixFrameImpl * pUnixFrameImpl = static_cast<XAP_UnixFrameImpl *>(g_object_get_data(G_OBJECT(w), "user_data"));


	if (gtk_im_context_filter_keypress(pUnixFrameImpl->getIMContext(), e)) {
		pUnixFrameImpl->queueIMReset ();

		if ((e->state & GDK_MOD1_MASK) ||
			(e->state & GDK_MOD3_MASK) ||
			(e->state & GDK_MOD4_MASK))
			return 0;


		g_signal_stop_emission (G_OBJECT(w),
								g_signal_lookup ("key_press_event",
												 G_OBJECT_TYPE (w)), 0);
		return 1;
	}

	XAP_Frame* pFrame = pUnixFrameImpl->getFrame();
	pUnixFrameImpl->setTimeOfLastEvent(e->time);
	AV_View * pView = pFrame->getCurrentView();
	ev_UnixKeyboard * pUnixKeyboard = static_cast<ev_UnixKeyboard *>(pFrame->getKeyboard());

	if (pView)
		pUnixKeyboard->keyPressEvent(pView, e);


	switch (e->keyval) {
	case GDK_KEY_Tab:
	case GDK_KEY_ISO_Left_Tab:
	case GDK_KEY_Left:
	case GDK_KEY_Up:
	case GDK_KEY_Right:
	case GDK_KEY_Down:
		return TRUE;
		break;
	}

	return FALSE;
}
