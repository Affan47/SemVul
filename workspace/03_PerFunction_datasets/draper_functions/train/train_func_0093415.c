gntdev_release(struct inode *inode, struct file *flip)
{
	struct gntdev_priv *priv = flip->private_data;
	struct grant_map *map;

	pr_debug("priv %p\n", priv);

	mutex_lock(&priv->lock);
	while (!list_empty(&priv->maps)) {
		map = list_entry(priv->maps.next, struct grant_map, next);
		list_del(&map->next);
		gntdev_put_map(NULL , map);
	}
	WARN_ON(!list_empty(&priv->freeable_maps));
	mutex_unlock(&priv->lock);

	if (use_ptemod)
		mmu_notifier_unregister(&priv->mn, priv->mm);
	kfree(priv);
	return 0;
}
