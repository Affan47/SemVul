media_transport_release(struct media_transport *transport,
					const char *accesstype)
{
	if (g_strstr_len(accesstype, -1, "r") != NULL) {
		transport->read_lock = FALSE;
		DBG("Transport %s: read lock released", transport->path);
	}

	if (g_strstr_len(accesstype, -1, "w") != NULL) {
		transport->write_lock = FALSE;
		DBG("Transport %s: write lock released", transport->path);
	}

	return TRUE;
}
