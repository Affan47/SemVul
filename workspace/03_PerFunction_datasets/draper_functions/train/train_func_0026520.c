concat_block_markbad(struct mtd_info *mtd, loff_t ofs)
{
	struct mtd_concat *concat = CONCAT(mtd);
	int i, err = -EINVAL;

	for (i = 0; i < concat->num_subdev; i++) {
		struct mtd_info *subdev = concat->subdev[i];

		if (ofs >= subdev->size) {
			ofs -= subdev->size;
			continue;
		}

		err = mtd_block_markbad(subdev, ofs);
		if (!err)
			mtd->ecc_stats.badblocks++;
		break;
	}

	return err;
}
