ssd_start_io_acct(struct ssd_cmd *cmd)
{
	struct ssd_device *dev = cmd->dev;
	struct bio *bio = cmd->bio;
	int rw = bio_data_dir(bio);

#if ((LINUX_VERSION_CODE >= KERNEL_VERSION(3,0,0)) || (defined RHEL_MAJOR && RHEL_MAJOR == 6 && RHEL_MINOR >= 7))
	int cpu = part_stat_lock();
	struct hd_struct *part = disk_map_sector_rcu(dev->gd, bio_start(bio));
	part_round_stats(cpu, part);
	part_stat_inc(cpu, part, ios[rw]);
	part_stat_add(cpu, part, sectors[rw], bio_sectors(bio));
	part_inc_in_flight(part, rw);
	part_stat_unlock();
#elif (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,27))
	int cpu = part_stat_lock();
	struct hd_struct *part = &dev->gd->part0;
	part_round_stats(cpu, part);
	part_stat_inc(cpu, part, ios[rw]);
	part_stat_add(cpu, part, sectors[rw], bio_sectors(bio));
	part_stat_unlock();
	part->in_flight[rw] = atomic_inc_return(&dev->in_flight[rw]);
#elif (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,14))
	preempt_disable();
	disk_round_stats(dev->gd);
	preempt_enable();
	disk_stat_inc(dev->gd, ios[rw]);
	disk_stat_add(dev->gd, sectors[rw], bio_sectors(bio));
	dev->gd->in_flight = atomic_inc_return(&dev->in_flight[0]);
#else
	preempt_disable();
	disk_round_stats(dev->gd);
	preempt_enable();
	if (rw == WRITE) {
		disk_stat_inc(dev->gd, writes);
		disk_stat_add(dev->gd, write_sectors, bio_sectors(bio));
	} else {
		disk_stat_inc(dev->gd, reads);
		disk_stat_add(dev->gd, read_sectors, bio_sectors(bio));
	}
	dev->gd->in_flight = atomic_inc_return(&dev->in_flight[0]);
#endif

	cmd->start_time = jiffies;
}
