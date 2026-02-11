gnome_rr_config_apply_with_time (GnomeRRConfig *config,
				 GnomeRRScreen *screen,
				 guint32        timestamp,
				 GError       **error)
{
    CrtcAssignment *assignment;
    GnomeOutputInfo **outputs;
    gboolean result = FALSE;

    outputs = make_outputs (config);

    assignment = crtc_assignment_new (screen, outputs, error);

    outputs_free (outputs);

    if (assignment)
    {
	if (crtc_assignment_apply (assignment, timestamp, error))
	    result = TRUE;

	crtc_assignment_free (assignment);

	gdk_flush ();
    }

    return result;
}
