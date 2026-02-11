query_esw_vport_cvlan(struct mlx5_core_dev *dev, u32 vport,
				 u16 *vlan, u8 *qos)
{
	u32 out[MLX5_ST_SZ_DW(query_esw_vport_context_out)];
	int err;
	bool cvlan_strip;
	bool cvlan_insert;

	memset(out, 0, sizeof(out));

	*vlan = 0;
	*qos = 0;

	if (!MLX5_CAP_ESW(dev, vport_cvlan_strip) ||
	    !MLX5_CAP_ESW(dev, vport_cvlan_insert_if_not_exist))
		return -ENOTSUPP;

	err = query_esw_vport_context_cmd(dev, vport, out, sizeof(out));
	if (err)
		goto out;

	cvlan_strip = MLX5_GET(query_esw_vport_context_out, out,
			       esw_vport_context.vport_cvlan_strip);

	cvlan_insert = MLX5_GET(query_esw_vport_context_out, out,
				esw_vport_context.vport_cvlan_insert);

	if (cvlan_strip || cvlan_insert) {
		*vlan = MLX5_GET(query_esw_vport_context_out, out,
				 esw_vport_context.cvlan_id);
		*qos = MLX5_GET(query_esw_vport_context_out, out,
				esw_vport_context.cvlan_pcp);
	}

	esw_debug(dev, "Query Vport[%d] cvlan: VLAN %d qos=%d\n",
		  vport, *vlan, *qos);
out:
	return err;
}
