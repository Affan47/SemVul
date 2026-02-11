_ledmon_execute(void)
{
	int restart = 0;
	status_t status = STATUS_SUCCESS;


	list_for_each(ledmon_block_list, _revalidate_dev);

	sysfs_block_device_for_each(_add_block);

	list_for_each(ledmon_block_list, _send_msg);

	list_for_each(ledmon_block_list, _flush_msg);

	list_for_each_parm(ledmon_block_list, _check_block_dev, &restart);

	list_for_each(ledmon_block_list, _invalidate_dev);

	if (restart) {

		list_for_each(ledmon_block_list, block_device_fini);
		list_fini(ledmon_block_list);
		status = list_init(&ledmon_block_list);
		if (status != STATUS_SUCCESS) {
			log_debug("%s(): list_init() failed (status=%s).",
				  __func__, strstatus(status));
			exit(EXIT_FAILURE);
		}
	}
}
