e_meeting_xfb_data_clear (EMeetingXfbData *xfb)
{
	g_return_if_fail (xfb != NULL);


	if (xfb->summary != NULL) {
		g_free (xfb->summary);
		xfb->summary = NULL;
	}
	if (xfb->location != NULL) {
		g_free (xfb->location);
		xfb->location = NULL;
	}
}
