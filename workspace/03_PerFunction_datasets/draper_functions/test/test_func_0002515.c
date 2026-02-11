concat_suspend(struct mtd_info *mtd)
{
	struct mtd_concat *concat = CONCAT(mtd);
	int i, rc = 0;

	for (i = 0; i < concat->num_subdev; i++) {
		struct mtd_info *subdev = concat->subdev[i];
		if ((rc = mtd_suspend(subdev)) < 0)
			return rc;
	}
	return rc;
}
