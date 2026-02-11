brasero_burn_options_message_response_span_cb (BraseroDiscMessage *message,
					       GtkResponseType response,
					       BraseroBurnOptions *self)
{
	if (response == GTK_RESPONSE_OK) {
		BraseroBurnOptionsPrivate *priv;

		priv = BRASERO_BURN_OPTIONS_PRIVATE (self);
		brasero_session_span_start (BRASERO_SESSION_SPAN (priv->session));
		if (brasero_session_span_next (BRASERO_SESSION_SPAN (priv->session)) == BRASERO_BURN_ERR)
			BRASERO_BURN_LOG ("Spanning failed\n");
	}
}
