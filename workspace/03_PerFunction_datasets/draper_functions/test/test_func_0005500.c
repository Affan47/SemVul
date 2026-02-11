free_dev(struct mapped_device *md)
{
	int minor = MINOR(disk_devt(md->disk));

	unlock_fs(md);

	cleanup_mapped_device(md);
	if (md->use_blk_mq)
		blk_mq_free_tag_set(&md->tag_set);

	free_table_devices(&md->table_devices);
	dm_stats_cleanup(&md->stats);
	free_minor(minor);

	module_put(THIS_MODULE);
	kfree(md);
}
