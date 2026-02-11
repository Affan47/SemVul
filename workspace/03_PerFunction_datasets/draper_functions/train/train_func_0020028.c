mlx5e_create_flow_tables(struct mlx5e_priv *priv)
{
	int err;

	err = mlx5e_create_main_flow_table(priv);
	if (err)
		return err;

	err = mlx5e_create_vlan_flow_table(priv);
	if (err)
		goto err_destroy_main_flow_table;

	err = mlx5e_add_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_UNTAGGED, 0);
	if (err)
		goto err_destroy_vlan_flow_table;

	return 0;

err_destroy_vlan_flow_table:
	mlx5e_destroy_vlan_flow_table(priv);

err_destroy_main_flow_table:
	mlx5e_destroy_main_flow_table(priv);

	return err;
}
