mlx4_err_rule(struct mlx4_dev *dev, char *str,
			  struct mlx4_net_trans_rule *rule)
{
#define BUF_SIZE 256
	struct mlx4_spec_list *cur;
	char buf[BUF_SIZE];
	int len = 0;

	mlx4_err(dev, "%s", str);
	len += snprintf(buf + len, BUF_SIZE - len,
			"port = %d prio = 0x%x qp = 0x%x ",
			rule->port, rule->priority, rule->qpn);

	list_for_each_entry(cur, &rule->list, list) {
		switch (cur->id) {
		case MLX4_NET_TRANS_RULE_ID_ETH:
			len += snprintf(buf + len, BUF_SIZE - len,
					"dmac = %pM ", &cur->eth.dst_mac);
			if (cur->eth.ether_type)
				len += snprintf(buf + len, BUF_SIZE - len,
						"ethertype = 0x%x ",
						be16_to_cpu(cur->eth.ether_type));
			if (cur->eth.vlan_id)
				len += snprintf(buf + len, BUF_SIZE - len,
						"vlan-id = %d ",
						be16_to_cpu(cur->eth.vlan_id));
			break;

		case MLX4_NET_TRANS_RULE_ID_IPV4:
			if (cur->ipv4.src_ip)
				len += snprintf(buf + len, BUF_SIZE - len,
						"src-ip = %pI4 ",
						&cur->ipv4.src_ip);
			if (cur->ipv4.dst_ip)
				len += snprintf(buf + len, BUF_SIZE - len,
						"dst-ip = %pI4 ",
						&cur->ipv4.dst_ip);
			break;

		case MLX4_NET_TRANS_RULE_ID_TCP:
		case MLX4_NET_TRANS_RULE_ID_UDP:
			if (cur->tcp_udp.src_port)
				len += snprintf(buf + len, BUF_SIZE - len,
						"src-port = %d ",
						be16_to_cpu(cur->tcp_udp.src_port));
			if (cur->tcp_udp.dst_port)
				len += snprintf(buf + len, BUF_SIZE - len,
						"dst-port = %d ",
						be16_to_cpu(cur->tcp_udp.dst_port));
			break;

		case MLX4_NET_TRANS_RULE_ID_IB:
			len += snprintf(buf + len, BUF_SIZE - len,
					"dst-gid = %pI6\n", cur->ib.dst_gid);
			len += snprintf(buf + len, BUF_SIZE - len,
					"dst-gid-mask = %pI6\n",
					cur->ib.dst_gid_msk);
			break;

		case MLX4_NET_TRANS_RULE_ID_VXLAN:
			len += snprintf(buf + len, BUF_SIZE - len,
					"VNID = %d ", be32_to_cpu(cur->vxlan.vni));
			break;
		case MLX4_NET_TRANS_RULE_ID_IPV6:
			break;

		default:
			break;
		}
	}
	len += snprintf(buf + len, BUF_SIZE - len, "\n");
	mlx4_err(dev, "%s", buf);

	if (len >= BUF_SIZE)
		mlx4_err(dev, "Network rule error message was truncated, print buffer is too small\n");
}
