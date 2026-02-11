wl18xx_conf_init(struct wl1271 *wl, struct device *dev)
{
	struct wl18xx_priv *priv = wl->priv;

	if (wl18xx_load_conf_file(dev, &wl->conf, &priv->conf) < 0) {
		wl1271_warning("falling back to default config");


		memcpy(&wl->conf, &wl18xx_conf, sizeof(wl->conf));

		memcpy(&priv->conf, &wl18xx_default_priv_conf,
		       sizeof(priv->conf));
	}

	return 0;
}
