sm_remove_dev(struct mtd_blktrans_dev *dev)
{
	struct sm_ftl *ftl = dev->priv;
	int i;

	del_mtd_blktrans_dev(dev);
	ftl->trans = NULL;

	for (i = 0 ; i < ftl->zone_count; i++) {

		if (!ftl->zones[i].initialized)
			continue;

		kfree(ftl->zones[i].lba_to_phys_table);
		kfifo_free(&ftl->zones[i].free_sectors);
	}

	sm_delete_sysfs_attributes(ftl);
	kfree(ftl->cis_buffer);
	kfree(ftl->zones);
	kfree(ftl->cache_data);
	kfree(ftl);
}
