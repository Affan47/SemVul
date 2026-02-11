__core_scsi3_write_aptpl_to_file(
	struct se_device *dev,
	unsigned char *buf)
{
	struct t10_wwn *wwn = &dev->t10_wwn;
	struct file *file;
	int flags = O_RDWR | O_CREAT | O_TRUNC;
	char path[512];
	u32 pr_aptpl_buf_len;
	int ret;

	memset(path, 0, 512);

	if (strlen(&wwn->unit_serial[0]) >= 512) {
		pr_err("WWN value for struct se_device does not fit"
			" into path buffer\n");
		return -EMSGSIZE;
	}

	snprintf(path, 512, "/var/target/pr/aptpl_%s", &wwn->unit_serial[0]);
	file = filp_open(path, flags, 0600);
	if (IS_ERR(file)) {
		pr_err("filp_open(%s) for APTPL metadata"
			" failed\n", path);
		return PTR_ERR(file);
	}

	pr_aptpl_buf_len = (strlen(buf) + 1);

	ret = kernel_write(file, buf, pr_aptpl_buf_len, 0);

	if (ret < 0)
		pr_debug("Error writing APTPL metadata file: %s\n", path);
	fput(file);

	return (ret < 0) ? -EIO : 0;
}
