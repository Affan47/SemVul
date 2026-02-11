process_readd_disk(struct mddev *mddev, struct cluster_msg *msg)
{
	struct md_rdev *rdev = md_find_rdev_nr_rcu(mddev,
						   le32_to_cpu(msg->raid_slot));

	if (rdev && test_bit(Faulty, &rdev->flags))
		clear_bit(Faulty, &rdev->flags);
	else
		pr_warn("%s: %d Could not find disk(%d) which is faulty",
			__func__, __LINE__, le32_to_cpu(msg->raid_slot));
}
