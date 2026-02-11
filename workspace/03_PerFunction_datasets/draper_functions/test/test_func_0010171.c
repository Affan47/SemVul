mlx5_ib_odp_find_mr_lkey(struct mlx5_ib_dev *dev,
						   u32 key)
{
	u32 base_key = mlx5_base_mkey(key);
	struct mlx5_core_mr *mmr = __mlx5_mr_lookup(dev->mdev, base_key);
	struct mlx5_ib_mr *mr = container_of(mmr, struct mlx5_ib_mr, mmr);

	if (!mmr || mmr->key != key || !mr->live)
		return NULL;

	return container_of(mmr, struct mlx5_ib_mr, mmr);
}
