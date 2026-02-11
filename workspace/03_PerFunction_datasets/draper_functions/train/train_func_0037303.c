mlx5_eswitch_get_vport_config(struct mlx5_eswitch *esw,
				  int vport, struct ifla_vf_info *ivi)
{
	u16 vlan;
	u8 qos;

	if (!ESW_ALLOWED(esw))
		return -EPERM;
	if (!LEGAL_VPORT(esw, vport))
		return -EINVAL;

	memset(ivi, 0, sizeof(*ivi));
	ivi->vf = vport - 1;

	mlx5_query_nic_vport_mac_address(esw->dev, vport, ivi->mac);
	ivi->linkstate = mlx5_query_vport_admin_state(esw->dev,
						      MLX5_QUERY_VPORT_STATE_IN_OP_MOD_ESW_VPORT,
						      vport);
	query_esw_vport_cvlan(esw->dev, vport, &vlan, &qos);
	ivi->vlan = vlan;
	ivi->qos = qos;
	ivi->spoofchk = 0;

	return 0;
}
