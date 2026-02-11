isr_status_change(struct ipw2100_priv *priv, int status)
{
	int i;

	if (status == IPW_STATE_SCANNING &&
	    priv->status & STATUS_ASSOCIATED &&
	    !(priv->status & STATUS_SCANNING)) {
		IPW_DEBUG_INFO("Scan detected while associated, with "
			       "no scan request.  Restarting firmware.\n");


		schedule_reset(priv);
	}

	for (i = 0; status_handlers[i].status != -1; i++) {
		if (status == status_handlers[i].status) {
			IPW_DEBUG_NOTIF("Status change: %s\n",
					status_handlers[i].name);
			if (status_handlers[i].cb)
				status_handlers[i].cb(priv, status);
			priv->wstats.status = status;
			return;
		}
	}

	IPW_DEBUG_NOTIF("unknown status received: %04x\n", status);
}
