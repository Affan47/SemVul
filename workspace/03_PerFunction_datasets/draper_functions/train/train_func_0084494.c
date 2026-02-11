key_release_event(GtkWidget* w, GdkEventKey* e)
{
	XAP_UnixFrameImpl * pUnixFrameImpl = static_cast<XAP_UnixFrameImpl *>(g_object_get_data(G_OBJECT(w), "user_data"));


	if (gtk_im_context_filter_keypress(pUnixFrameImpl->getIMContext(), e)) {
	    UT_DEBUGMSG(("IMCONTEXT keyevent swallow: %u\n", e->keyval));
		pUnixFrameImpl->queueIMReset ();
	    return 0;
	}
	return TRUE;
}
