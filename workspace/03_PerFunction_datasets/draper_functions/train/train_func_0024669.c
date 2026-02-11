aipd_cleanup (NMDevice *self)
{
	NMDevicePrivate *priv = NM_DEVICE_GET_PRIVATE (self);

	if (priv->aipd_watch) {
		g_source_remove (priv->aipd_watch);
		priv->aipd_watch = 0;
	}

	if (priv->aipd_pid > 0) {
		kill (priv->aipd_pid, SIGKILL);


		nm_log_dbg (LOGD_AUTOIP4, "waiting for avahi-autoipd pid %d to exit", priv->aipd_pid);
		waitpid (priv->aipd_pid, NULL, 0);
		nm_log_dbg (LOGD_AUTOIP4, "avahi-autoip pid %d cleaned up", priv->aipd_pid);

		priv->aipd_pid = -1;
	}

	aipd_timeout_remove (self);
}
