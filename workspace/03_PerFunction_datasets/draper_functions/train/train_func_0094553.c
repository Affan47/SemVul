ipw2100_msg_initialize(struct ipw2100_priv *priv)
{
	int i;

	INIT_LIST_HEAD(&priv->msg_free_list);
	INIT_LIST_HEAD(&priv->msg_pend_list);

	for (i = 0; i < IPW_COMMAND_POOL_SIZE; i++)
		list_add_tail(&priv->msg_buffers[i].list, &priv->msg_free_list);
	SET_STAT(&priv->msg_free_stat, i);

	return 0;
}
