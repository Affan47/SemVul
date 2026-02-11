iwl_dbgfs_protection_mode_read(struct file *file,
					char __user *user_buf,
					size_t count, loff_t *ppos)
{
	struct iwl_priv *priv = (struct iwl_priv *)file->private_data;

	int pos = 0;
	char buf[40];
	const size_t bufsz = sizeof(buf);

	if (priv->cfg->ht_params)
		pos += scnprintf(buf + pos, bufsz - pos,
			 "use %s for aggregation\n",
			 (priv->hw_params.use_rts_for_aggregation) ?
				"rts/cts" : "cts-to-self");
	else
		pos += scnprintf(buf + pos, bufsz - pos, "N/A");

	return simple_read_from_buffer(user_buf, count, ppos, buf, pos);
}
