core_alloc_rtpi(struct se_lun *lun, struct se_device *dev)
{
	struct se_lun *tmp;

	spin_lock(&dev->se_port_lock);
	if (dev->export_count == 0x0000ffff) {
		pr_warn("Reached dev->dev_port_count =="
				" 0x0000ffff\n");
		spin_unlock(&dev->se_port_lock);
		return -ENOSPC;
	}
again:


	lun->lun_rtpi = dev->dev_rpti_counter++;
	if (!lun->lun_rtpi)
		goto again;

	list_for_each_entry(tmp, &dev->dev_sep_list, lun_dev_link) {


		if (lun->lun_rtpi == tmp->lun_rtpi)
			goto again;
	}
	spin_unlock(&dev->se_port_lock);

	return 0;
}
