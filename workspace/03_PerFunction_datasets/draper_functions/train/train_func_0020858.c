delay_dtr(struct dm_target *ti)
{
	struct delay_c *dc = ti->private;

	destroy_workqueue(dc->kdelayd_wq);

	dm_put_device(ti, dc->dev_read);

	if (dc->dev_write)
		dm_put_device(ti, dc->dev_write);

	kfree(dc);
}
