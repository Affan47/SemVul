gst_binding_set_xid (gstPlay *play, gulong xid) {
	if (play == NULL)
		return;

	play->xid = xid;
	if (play->overlay != NULL && GST_IS_X_OVERLAY (play->overlay))
		gst_x_overlay_set_xwindow_id (play->overlay, xid);
}
