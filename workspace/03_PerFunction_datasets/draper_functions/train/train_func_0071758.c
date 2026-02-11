ipw2100_initialize_ordinals(struct ipw2100_priv *priv)
{
	struct ipw2100_ordinals *ord = &priv->ordinals;

	IPW_DEBUG_INFO("enter\n");

	read_register(priv->net_dev, IPW_MEM_HOST_SHARED_ORDINALS_TABLE_1,
		      &ord->table1_addr);

	read_register(priv->net_dev, IPW_MEM_HOST_SHARED_ORDINALS_TABLE_2,
		      &ord->table2_addr);

	read_nic_dword(priv->net_dev, ord->table1_addr, &ord->table1_size);
	read_nic_dword(priv->net_dev, ord->table2_addr, &ord->table2_size);

	ord->table2_size &= 0x0000FFFF;

	IPW_DEBUG_INFO("table 1 size: %d\n", ord->table1_size);
	IPW_DEBUG_INFO("table 2 size: %d\n", ord->table2_size);
	IPW_DEBUG_INFO("exit\n");
}
