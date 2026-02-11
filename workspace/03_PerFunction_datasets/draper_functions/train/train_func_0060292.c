handle_eth_header_mcast_prio(struct mlx4_net_trans_rule_hw_ctrl *ctrl,
					 struct _rule_hw *eth_header)
{
	if (is_multicast_ether_addr(eth_header->eth.dst_mac) ||
	    is_broadcast_ether_addr(eth_header->eth.dst_mac)) {
		struct mlx4_net_trans_rule_hw_eth *eth =
			(struct mlx4_net_trans_rule_hw_eth *)eth_header;
		struct _rule_hw *next_rule = (struct _rule_hw *)(eth + 1);
		bool last_rule = next_rule->size == 0 && next_rule->id == 0 &&
			next_rule->rsvd == 0;

		if (last_rule)
			ctrl->prio = cpu_to_be16(MLX4_DOMAIN_NIC);
	}
}
