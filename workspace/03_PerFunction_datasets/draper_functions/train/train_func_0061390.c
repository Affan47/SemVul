gluebi_put_device(struct mtd_info *mtd)
{
	struct gluebi_device *gluebi;

	gluebi = container_of(mtd, struct gluebi_device, mtd);
	mutex_lock(&devices_mutex);
	gluebi->refcnt -= 1;
	if (gluebi->refcnt == 0)
		ubi_close_volume(gluebi->desc);
	module_put(THIS_MODULE);
	mutex_unlock(&devices_mutex);
}
