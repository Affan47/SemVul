mlx5e_execute_action(struct mlx5e_priv *priv,
				 struct mlx5e_eth_addr_hash_node *hn)
{
	switch (hn->action) {
	case MLX5E_ACTION_ADD:
		mlx5e_add_eth_addr_rule(priv, &hn->ai, MLX5E_FULLMATCH);
		hn->action = MLX5E_ACTION_NONE;
		break;

	case MLX5E_ACTION_DEL:
		mlx5e_del_eth_addr_from_flow_table(priv, &hn->ai);
		mlx5e_del_eth_addr_from_hash(hn);
		break;
	}
}
