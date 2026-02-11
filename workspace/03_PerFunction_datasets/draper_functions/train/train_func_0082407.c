block2mtd_exit(void)
{
	struct list_head *pos, *next;


	list_for_each_safe(pos, next, &blkmtd_device_list) {
		struct block2mtd_dev *dev = list_entry(pos, typeof(*dev), list);
		block2mtd_sync(&dev->mtd);
		mtd_device_unregister(&dev->mtd);
		mutex_destroy(&dev->write_mutex);
		pr_info("mtd%d: [%s] removed\n",
			dev->mtd.index,
			dev->mtd.name + strlen("block2mtd: "));
		list_del(&dev->list);
		block2mtd_free_device(dev);
	}
}
