ide_floppy_get_format_capacities(ide_drive_t *drive,
					    struct ide_atapi_pc *pc,
					    int __user *arg)
{
	struct ide_disk_obj *floppy = drive->driver_data;
	int i, blocks, length, u_array_size, u_index;
	int __user *argp;
	u8 pc_buf[256], header_len, desc_cnt;

	if (get_user(u_array_size, arg))
		return -EFAULT;

	if (u_array_size <= 0)
		return -EINVAL;

	ide_floppy_create_read_capacity_cmd(pc);

	if (ide_queue_pc_tail(drive, floppy->disk, pc, pc_buf, pc->req_xfer)) {
		printk(KERN_ERR "ide-floppy: Can't get floppy parameters\n");
		return -EIO;
	}

	header_len = pc_buf[3];
	desc_cnt = header_len / 8;

	u_index = 0;
	argp = arg + 1;


	for (i = 1; i < desc_cnt; i++) {
		unsigned int desc_start = 4 + i*8;

		if (u_index >= u_array_size)
			break;

		blocks = be32_to_cpup((__be32 *)&pc_buf[desc_start]);
		length = be16_to_cpup((__be16 *)&pc_buf[desc_start + 6]);

		if (put_user(blocks, argp))
			return -EFAULT;

		++argp;

		if (put_user(length, argp))
			return -EFAULT;

		++argp;

		++u_index;
	}

	if (put_user(u_index, arg))
		return -EFAULT;

	return 0;
}
