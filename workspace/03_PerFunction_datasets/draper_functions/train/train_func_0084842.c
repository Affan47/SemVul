wil_err_ratelimited(struct wil6210_priv *wil, const char *fmt, ...)
{
	if (net_ratelimit()) {
		struct net_device *ndev = wil_to_ndev(wil);
		struct va_format vaf = {
			.fmt = fmt,
		};
		va_list args;

		va_start(args, fmt);
		vaf.va = &args;
		netdev_err(ndev, "%pV", &vaf);
		trace_wil6210_log_err(&vaf);
		va_end(args);
	}
}
