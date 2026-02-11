does_sb_need_changing(struct mddev *mddev)
{
	struct md_rdev *rdev;
	struct mdp_superblock_1 *sb;
	int role;


	rdev_for_each(rdev, mddev)
		if ((rdev->raid_disk >= 0) && !test_bit(Faulty, &rdev->flags))
			break;


	if (!rdev)
		return false;

	sb = page_address(rdev->sb_page);

	rdev_for_each(rdev, mddev) {
		role = le16_to_cpu(sb->dev_roles[rdev->desc_nr]);

		if (role == 0xffff && rdev->raid_disk >=0 &&
		    !test_bit(Faulty, &rdev->flags))
			return true;

		if (test_bit(Faulty, &rdev->flags) && (role < 0xfffd))
			return true;
	}


	if ((mddev->dev_sectors != le64_to_cpu(sb->size)) ||
	    (mddev->reshape_position != le64_to_cpu(sb->reshape_position)) ||
	    (mddev->layout != le32_to_cpu(sb->layout)) ||
	    (mddev->raid_disks != le32_to_cpu(sb->raid_disks)) ||
	    (mddev->chunk_sectors != le32_to_cpu(sb->chunksize)))
		return true;

	return false;
}
