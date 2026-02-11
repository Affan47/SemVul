gst_binding_has_video (gstPlay *play) {
	if (!isValid (play)) return FALSE;

	gint cur_video;
	g_object_get (play->element, "current-video", &cur_video, NULL);
	if (cur_video == -1) return FALSE;
	else return TRUE;
}
