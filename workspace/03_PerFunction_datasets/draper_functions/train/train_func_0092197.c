aac_src_check_health(struct aac_dev *dev)
{
	u32 status = src_readl(dev, MUnit.OMR);


	if (unlikely(status & KERNEL_PANIC))
		goto err_blink;


	if (unlikely(status & SELF_TEST_FAILED))
		goto err_out;


	if (unlikely(status & MONITOR_PANIC))
		goto err_out;


	if (unlikely(!(status & KERNEL_UP_AND_RUNNING)))
		return -3;


	return 0;

err_out:
	return -1;

err_blink:
	return (status > 16) & 0xFF;
}
