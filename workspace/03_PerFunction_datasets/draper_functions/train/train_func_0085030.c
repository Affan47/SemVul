hScrollChanged(GtkAdjustment * w, gpointer )
{
	XAP_UnixFrameImpl * pUnixFrameImpl = static_cast<XAP_UnixFrameImpl *>(g_object_get_data(G_OBJECT(w), "user_data"));
	XAP_Frame* pFrame = pUnixFrameImpl->getFrame();
	AV_View * pView = pFrame->getCurrentView();

	if (pView)
		pView->sendHorizontalScrollEvent(static_cast<UT_sint32>(gtk_adjustment_get_value(w)));
}
