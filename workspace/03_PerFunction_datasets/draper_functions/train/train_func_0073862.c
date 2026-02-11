rocker_port_ctrl_vlan_bridge(struct rocker_port *rocker_port,
					struct switchdev_trans *trans,
					int flags,
					const struct rocker_ctrl *ctrl,
					__be16 vlan_id)
{
	enum rocker_of_dpa_table_id goto_tbl =
		ROCKER_OF_DPA_TABLE_ID_ACL_POLICY;
	u32 group_id = ROCKER_GROUP_L2_FLOOD(vlan_id, 0);
	u32 tunnel_id = 0;
	int err;

	if (!rocker_port_is_bridged(rocker_port))
		return 0;

	err = rocker_flow_tbl_bridge(rocker_port, trans, flags,
				     ctrl->eth_dst, ctrl->eth_dst_mask,
				     vlan_id, tunnel_id,
				     goto_tbl, group_id, ctrl->copy_to_cpu);

	if (err)
		netdev_err(rocker_port->dev, "Error (%d) ctrl FLOOD\n", err);

	return err;
}
