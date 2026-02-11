soup_session_feature_real_attach (SoupSessionFeature *feature, SoupSession *session)
{
	g_object_weak_ref (G_OBJECT (session),
			   weak_notify_unref, g_object_ref (feature));

	if (SOUP_SESSION_FEATURE_GET_CLASS (feature)->request_queued) {
		g_signal_connect (session, "request_queued",
				  G_CALLBACK (request_queued), feature);
	}

	if (SOUP_SESSION_FEATURE_GET_CLASS (feature)->request_started) {
		g_signal_connect (session, "request_started",
				  G_CALLBACK (request_started), feature);
	}

	if (SOUP_SESSION_FEATURE_GET_CLASS (feature)->request_unqueued) {
		g_signal_connect (session, "request_unqueued",
				  G_CALLBACK (request_unqueued), feature);
	}
}
