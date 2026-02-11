scsi_vpd_tpg_id(struct scsi_device *sdev, int *rel_id)
{
	unsigned char *d;
	unsigned char __rcu *vpd_pg83;
	int group_id = -EAGAIN, rel_port = -1;

	rcu_read_lock();
	vpd_pg83 = rcu_dereference(sdev->vpd_pg83);
	if (!vpd_pg83) {
		rcu_read_unlock();
		return -ENXIO;
	}

	d = sdev->vpd_pg83 + 4;
	while (d < sdev->vpd_pg83 + sdev->vpd_pg83_len) {
		switch (d[1] & 0xf) {
		case 0x4:

			rel_port = get_unaligned_be16(&d[6]);
			break;
		case 0x5:

			group_id = get_unaligned_be16(&d[6]);
			break;
		default:
			break;
		}
		d += d[3] + 4;
	}
	rcu_read_unlock();

	if (group_id >= 0 && rel_id && rel_port != -1)
		*rel_id = rel_port;

	return group_id;
}
