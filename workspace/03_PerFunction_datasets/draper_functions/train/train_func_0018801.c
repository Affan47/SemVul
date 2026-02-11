reg_mr_callback(int status, void *context)
{
	struct mlx5_ib_mr *mr = context;
	struct mlx5_ib_dev *dev = mr->dev;
	struct mlx5_mr_cache *cache = &dev->cache;
	int c = order2idx(dev, mr->order);
	struct mlx5_cache_ent *ent = &cache->ent[c];
	u8 key;
	unsigned long flags;
	struct mlx5_mr_table *table = &dev->mdev->priv.mr_table;
	int err;

	spin_lock_irqsave(&ent->lock, flags);
	ent->pending--;
	spin_unlock_irqrestore(&ent->lock, flags);
	if (status) {
		mlx5_ib_warn(dev, "async reg mr failed. status %d\n", status);
		kfree(mr);
		dev->fill_delay = 1;
		mod_timer(&dev->delay_timer, jiffies + HZ);
		return;
	}

	if (mr->out.hdr.status) {
		mlx5_ib_warn(dev, "failed - status %d, syndorme 0x%x\n",
			     mr->out.hdr.status,
			     be32_to_cpu(mr->out.hdr.syndrome));
		kfree(mr);
		dev->fill_delay = 1;
		mod_timer(&dev->delay_timer, jiffies + HZ);
		return;
	}

	spin_lock_irqsave(&dev->mdev->priv.mkey_lock, flags);
	key = dev->mdev->priv.mkey_key++;
	spin_unlock_irqrestore(&dev->mdev->priv.mkey_lock, flags);
	mr->mmr.key = mlx5_idx_to_mkey(be32_to_cpu(mr->out.mkey) & 0xffffff) | key;

	cache->last_add = jiffies;

	spin_lock_irqsave(&ent->lock, flags);
	list_add_tail(&mr->list, &ent->head);
	ent->cur++;
	ent->size++;
	spin_unlock_irqrestore(&ent->lock, flags);

	write_lock_irqsave(&table->lock, flags);
	err = radix_tree_insert(&table->tree, mlx5_base_mkey(mr->mmr.key),
				&mr->mmr);
	if (err)
		pr_err("Error inserting to mr tree. 0x%x\n", -err);
	write_unlock_irqrestore(&table->lock, flags);
}
