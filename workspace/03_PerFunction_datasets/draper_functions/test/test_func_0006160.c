sdebug_remove_adapter(void)
{
        struct sdebug_host_info * sdbg_host = NULL;

        spin_lock(&sdebug_host_list_lock);
        if (!list_empty(&sdebug_host_list)) {
                sdbg_host = list_entry(sdebug_host_list.prev,
                                       struct sdebug_host_info, host_list);
		list_del(&sdbg_host->host_list);
	}
        spin_unlock(&sdebug_host_list_lock);

	if (!sdbg_host)
		return;

        device_unregister(&sdbg_host->dev);
        --scsi_debug_add_host;
}
