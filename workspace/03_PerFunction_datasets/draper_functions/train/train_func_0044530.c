mlx5_flow_rule_add_dest(struct mlx5_flow_rule *fr,
				   struct mlx5_flow_destination *new_dest)
{
	struct dest_node *dest_n;
	int err;

	dest_n = kzalloc(sizeof(*dest_n), GFP_KERNEL);
	if (!dest_n)
		return -ENOMEM;

	memcpy(&dest_n->dest, new_dest, sizeof(dest_n->dest));
	mutex_lock(&fr->mutex);
	list_add(&dest_n->list, &fr->dest_list);
	err = _mlx5_flow_rule_apply(fr);
	if (err) {
		list_del(&dest_n->list);
		kfree(dest_n);
	}
	mutex_unlock(&fr->mutex);
	return err;
}
