protocol_id_set(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct cmd_ds_mesh_config cmd;
	struct mrvl_mesh_defaults defs;
	struct mrvl_meshie *ie;
	struct lbs_private *priv = to_net_dev(dev)->ml_priv;
	uint32_t datum;
	int ret;

	memset(&cmd, 0, sizeof(cmd));
	ret = sscanf(buf, "%d", &datum);
	if ((ret != 1) || (datum > 255))
		return -EINVAL;


	ret = mesh_get_default_parameters(dev, &defs);

	cmd.length = cpu_to_le16(sizeof(struct mrvl_meshie));


	ie = (struct mrvl_meshie *) &cmd.data[0];
	memcpy(ie, &defs.meshie, sizeof(struct mrvl_meshie));

	ie->val.active_protocol_id = datum;

	ret = lbs_mesh_config_send(priv, &cmd, CMD_ACT_MESH_CONFIG_SET,
				   CMD_TYPE_MESH_SET_MESH_IE);
	if (ret)
		return ret;

	return strlen(buf);
}
