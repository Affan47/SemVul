atk_debugfs_ggrp_open(struct inode *inode, struct file *file)
{
	struct atk_data *data = inode->i_private;
	char *buf = NULL;
	union acpi_object *ret;
	u8 cls;
	int i;

	if (!data->enumerate_handle)
		return -ENODEV;
	if (!data->debugfs.id)
		return -EINVAL;

	cls = (data->debugfs.id & 0xff000000) >> 24;
	ret = atk_ggrp(data, cls);
	if (IS_ERR(ret))
		return PTR_ERR(ret);

	for (i = 0; i < ret->package.count; i++) {
		union acpi_object *pack = &ret->package.elements[i];
		union acpi_object *id;

		if (pack->type != ACPI_TYPE_PACKAGE)
			continue;
		if (!pack->package.count)
			continue;
		id = &pack->package.elements[0];
		if (id->integer.value == data->debugfs.id) {

			buf = kzalloc(512, GFP_KERNEL);
			if (!buf) {
				ACPI_FREE(ret);
				return -ENOMEM;
			}
			atk_pack_print(buf, 512, pack);
			break;
		}
	}
	ACPI_FREE(ret);

	if (!buf)
		return -EINVAL;

	file->private_data = buf;

	return nonseekable_open(inode, file);
}
