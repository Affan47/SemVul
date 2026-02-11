debug_handler (const char *log_domain, GLogLevelFlags log_level, const char *message, AlmanahApplication *self)
{

	if (self->priv->debug == TRUE) {
		g_log_default_handler (log_domain, log_level, message, NULL);
	}
}
