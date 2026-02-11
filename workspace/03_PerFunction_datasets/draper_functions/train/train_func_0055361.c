mlx4_en_ethtool_to_net_trans_rule(struct net_device *dev,
					     struct ethtool_rxnfc *cmd,
					     struct list_head *rule_list_h)
{
	int err;
	struct ethhdr *eth_spec;
	struct mlx4_spec_list *spec_l2;
	struct mlx4_en_priv *priv = netdev_priv(dev);

	err = mlx4_en_validate_flow(dev, cmd);
	if (err)
		return err;

	switch (cmd->fs.flow_type & ~(FLOW_EXT | FLOW_MAC_EXT)) {
	case ETHER_FLOW:
		spec_l2 = kzalloc(sizeof(*spec_l2), GFP_KERNEL);
		if (!spec_l2)
			return -ENOMEM;

		eth_spec = &cmd->fs.h_u.ether_spec;
		mlx4_en_ethtool_add_mac_rule(cmd, rule_list_h, spec_l2,
					     &eth_spec->h_dest[0]);
		spec_l2->eth.ether_type = eth_spec->h_proto;
		if (eth_spec->h_proto)
			spec_l2->eth.ether_type_enable = 1;
		break;
	case IP_USER_FLOW:
		err = add_ip_rule(priv, cmd, rule_list_h);
		break;
	case TCP_V4_FLOW:
		err = add_tcp_udp_rule(priv, cmd, rule_list_h, TCP_V4_FLOW);
		break;
	case UDP_V4_FLOW:
		err = add_tcp_udp_rule(priv, cmd, rule_list_h, UDP_V4_FLOW);
		break;
	}

	return err;
}
