rocker_port_fib_ipv4(struct rocker_port *rocker_port,
				struct switchdev_trans *trans, __be32 dst,
				int dst_len, const struct fib_info *fi,
				u32 tb_id, int flags)
{
	const struct fib_nh *nh;
	__be16 eth_type = htons(ETH_P_IP);
	__be32 dst_mask = inet_make_mask(dst_len);
	__be16 internal_vlan_id = rocker_port->internal_vlan_id;
	u32 priority = fi->fib_priority;
	enum rocker_of_dpa_table_id goto_tbl =
		ROCKER_OF_DPA_TABLE_ID_ACL_POLICY;
	u32 group_id;
	bool nh_on_port;
	bool has_gw;
	u32 index;
	int err;


	nh = fi->fib_nh;
	nh_on_port = (fi->fib_dev == rocker_port->dev);
	has_gw = !!nh->nh_gw;

	if (has_gw && nh_on_port) {
		err = rocker_port_ipv4_nh(rocker_port, trans, flags,
					  nh->nh_gw, &index);
		if (err)
			return err;

		group_id = ROCKER_GROUP_L3_UNICAST(index);
	} else {

		group_id = ROCKER_GROUP_L2_INTERFACE(internal_vlan_id, 0);
	}

	err = rocker_flow_tbl_ucast4_routing(rocker_port, trans, eth_type, dst,
					     dst_mask, priority, goto_tbl,
					     group_id, flags);
	if (err)
		netdev_err(rocker_port->dev, "Error (%d) IPv4 route %pI4\n",
			   err, &dst);

	return err;
}
