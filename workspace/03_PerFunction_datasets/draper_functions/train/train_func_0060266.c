audio_device_request_authorization(struct audio_device *dev,
					const char *uuid, service_auth_cb cb,
					void *user_data)
{
	struct dev_priv *priv = dev->priv;
	struct service_auth *auth;
	int err;

	auth = g_try_new0(struct service_auth, 1);
	if (!auth)
		return -ENOMEM;

	auth->cb = cb;
	auth->user_data = user_data;

	priv->auths = g_slist_append(priv->auths, auth);
	if (g_slist_length(priv->auths) > 1)
		return 0;

	if (priv->authorized || audio_device_is_connected(dev)) {
		priv->auth_idle_id = g_idle_add(auth_idle_cb, dev);
		return 0;
	}

	err = btd_request_authorization(&dev->src, &dev->dst, uuid, auth_cb,
					dev);
	if (err < 0) {
		priv->auths = g_slist_remove(priv->auths, auth);
		g_free(auth);
	}

	return err;
}
