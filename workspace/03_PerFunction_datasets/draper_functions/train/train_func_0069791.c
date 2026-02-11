cavan_block_device_init(struct cavan_block_device *bdev, void *context)
{
	if (bdev->read_block == NULL || bdev->write_block == NULL)
	{
		pr_red_info("Please set read_block and write_block");
		return -EINVAL;
	}

	if (bdev->block_size)
	{
		int shift = math_get_value_shift(bdev->block_size);

		if (bdev->block_shift && bdev->block_shift != shift)
		{
			pr_red_info("block shift not match");
			return -EINVAL;
		}

		bdev->block_shift = shift;
	}
	else if (bdev->block_shift)
	{
		bdev->block_size = 1 << bdev->block_shift;
	}
	else
	{
		pr_red_info("Please give block_size or block shift");
		return -EINVAL;
	}

	if (bdev->read_byte == NULL)
	{
		bdev->read_byte = cavan_block_device_read_byte_dummy;
	}

	if (bdev->write_byte == NULL)
	{
		bdev->write_byte = cavan_block_device_write_byte_dummy;
	}

	bdev->context = context;
	bdev->block_mask = bdev->block_size - 1;

#if CAVAN_BLOCK_DEVICE_DEBUG
	println("block_size = %d", bdev->block_size);
	println("block_shift = %d", bdev->block_shift);
	println("block_mask = 0x%08x", bdev->block_mask);
#endif

	return 0;
}
