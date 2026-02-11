gst_binding_load (gstPlay *play, char *uri) {
	if (isValid (play))
	{
		g_object_set (G_OBJECT (play->element), "uri", uri, NULL);
		if (gst_element_set_state (play->element, GST_STATE_PAUSED) != GST_STATE_CHANGE_FAILURE)
		    return TRUE;
	}

	return FALSE;
}
