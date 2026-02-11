wil_link_debugfs_show(struct seq_file *s, void *data)
{
	struct wil6210_priv *wil = s->private;
	struct station_info sinfo;
	int i, rc;

	for (i = 0; i < ARRAY_SIZE(wil->sta); i++) {
		struct wil_sta_info *p = &wil->sta[i];
		char *status = "unknown";

		switch (p->status) {
		case wil_sta_unused:
			status = "unused   ";
			break;
		case wil_sta_conn_pending:
			status = "pending  ";
			break;
		case wil_sta_connected:
			status = "connected";
			break;
		}
		seq_printf(s, "[%d] %pM %s\n", i, p->addr, status);

		if (p->status == wil_sta_connected) {
			rc = wil_cid_fill_sinfo(wil, i, &sinfo);
			if (rc)
				return rc;

			seq_printf(s, "  Tx_mcs = %d\n", sinfo.txrate.mcs);
			seq_printf(s, "  Rx_mcs = %d\n", sinfo.rxrate.mcs);
			seq_printf(s, "  SQ     = %d\n", sinfo.signal);
		}
	}

	return 0;
}
