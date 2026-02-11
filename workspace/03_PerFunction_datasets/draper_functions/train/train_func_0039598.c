validate_change_holder_cb (GdaHolder *holder, const GValue *value, GdaSet *set)
{

	GError *error = NULL;
	if (set->priv->read_only)
		g_set_error (&error, GDA_SET_ERROR, GDA_SET_READ_ONLY_ERROR, "%s", _("Data set does not allow modifications"));
	else {
#ifdef GDA_DEBUG_signal
		g_print (">> 'VALIDATE_HOLDER_CHANGE' from %s\n", __FUNCTION__);
#endif
		g_signal_emit (G_OBJECT (set), gda_set_signals[VALIDATE_HOLDER_CHANGE], 0, holder, value, &error);
#ifdef GDA_DEBUG_signal
		g_print ("<< 'VALIDATE_HOLDER_CHANGED' from %s\n", __FUNCTION__);
#endif
	}
	return error;
}
