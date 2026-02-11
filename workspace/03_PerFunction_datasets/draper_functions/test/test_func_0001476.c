sh_csi2_client_disconnect(struct sh_csi2 *priv)
{
	if (!priv->client)
		return;

	priv->client = NULL;

	pm_runtime_put(v4l2_get_subdevdata(&priv->subdev));
}
