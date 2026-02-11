get_next_record_to_update(struct mlx4_ib_dev *dev, u8 port,
				     struct mlx4_next_alias_guid_work *rec)
{
	unsigned long flags;
	int record_index;
	int ret = 0;

	spin_lock_irqsave(&dev->sriov.alias_guid.ag_work_lock, flags);
	record_index = get_low_record_time_index(dev, port, NULL);

	if (record_index < 0) {
		ret = -ENOENT;
		goto out;
	}

	set_required_record(dev, port, rec, record_index);
out:
	spin_unlock_irqrestore(&dev->sriov.alias_guid.ag_work_lock, flags);
	return ret;
}
