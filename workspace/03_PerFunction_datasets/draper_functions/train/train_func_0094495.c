vmw_cotable_alloc(struct vmw_private *dev_priv,
				       struct vmw_resource *ctx,
				       u32 type)
{
	struct vmw_cotable *vcotbl;
	int ret;
	u32 num_entries;

	if (unlikely(cotable_acc_size == 0))
		cotable_acc_size = ttm_round_pot(sizeof(struct vmw_cotable));

	ret = ttm_mem_global_alloc(vmw_mem_glob(dev_priv),
				   cotable_acc_size, false, true);
	if (unlikely(ret))
		return ERR_PTR(ret);

	vcotbl = kzalloc(sizeof(*vcotbl), GFP_KERNEL);
	if (unlikely(vcotbl == NULL)) {
		ret = -ENOMEM;
		goto out_no_alloc;
	}

	ret = vmw_resource_init(dev_priv, &vcotbl->res, true,
				vmw_cotable_free, &vmw_cotable_func);
	if (unlikely(ret != 0))
		goto out_no_init;

	INIT_LIST_HEAD(&vcotbl->resource_list);
	vcotbl->res.id = type;
	vcotbl->res.backup_size = PAGE_SIZE;
	num_entries = PAGE_SIZE / co_info[type].size;
	if (num_entries < co_info[type].min_initial_entries) {
		vcotbl->res.backup_size = co_info[type].min_initial_entries *
			co_info[type].size;
		vcotbl->res.backup_size =
			(vcotbl->res.backup_size + PAGE_SIZE - 1) & PAGE_MASK;
	}

	vcotbl->scrubbed = true;
	vcotbl->seen_entries = -1;
	vcotbl->type = type;
	vcotbl->ctx = ctx;

	vmw_resource_activate(&vcotbl->res, vmw_hw_cotable_destroy);

	return &vcotbl->res;

out_no_init:
	kfree(vcotbl);
out_no_alloc:
	ttm_mem_global_free(vmw_mem_glob(dev_priv), cotable_acc_size);
	return ERR_PTR(ret);
}
