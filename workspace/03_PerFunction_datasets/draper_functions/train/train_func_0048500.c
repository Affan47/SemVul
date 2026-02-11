alloc_fr(void *ft,
				       u8 match_criteria_enable,
				       u32 *match_criteria,
				       u32 *match_value,
				       u32 action,
				       u32 flow_tag)
{
	struct mlx5_flow_rule *fr = kzalloc(sizeof(*fr), GFP_KERNEL);

	if (!fr)
		return NULL;

	fr->match_criteria = kzalloc(MLX5_ST_SZ_BYTES(fte_match_param), GFP_KERNEL);
	fr->match_value = kzalloc(MLX5_ST_SZ_BYTES(fte_match_param), GFP_KERNEL);
	if (!fr->match_criteria || !fr->match_value) {
		kfree(fr->match_criteria);
		kfree(fr->match_value);
		kfree(fr);
		return NULL;
	}

	memcpy(fr->match_criteria, match_criteria, MLX5_ST_SZ_BYTES(fte_match_param));
	memcpy(fr->match_value, match_value, MLX5_ST_SZ_BYTES(fte_match_param));
	fr->match_criteria_enable = match_criteria_enable;
	fr->flow_tag = flow_tag;
	fr->action = action;

	mutex_init(&fr->mutex);
	INIT_LIST_HEAD(&fr->dest_list);
	atomic_set(&fr->refcount, 0);
	fr->ft = ft;
	return fr;
}
