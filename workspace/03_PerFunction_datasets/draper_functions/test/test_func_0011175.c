hot_add_req(struct work_struct *dummy)
{
	struct dm_hot_add_response resp;
#ifdef CONFIG_MEMORY_HOTPLUG
	unsigned long pg_start, pfn_cnt;
	unsigned long rg_start, rg_sz;
#endif
	struct hv_dynmem_device *dm = &dm_device;

	memset(&resp, 0, sizeof(struct dm_hot_add_response));
	resp.hdr.type = DM_MEM_HOT_ADD_RESPONSE;
	resp.hdr.size = sizeof(struct dm_hot_add_response);

#ifdef CONFIG_MEMORY_HOTPLUG
	pg_start = dm->ha_wrk.ha_page_range.finfo.start_page;
	pfn_cnt = dm->ha_wrk.ha_page_range.finfo.page_cnt;

	rg_start = dm->ha_wrk.ha_region_range.finfo.start_page;
	rg_sz = dm->ha_wrk.ha_region_range.finfo.page_cnt;

	if ((rg_start == 0) && (!dm->host_specified_ha_region)) {
		unsigned long region_size;
		unsigned long region_start;


		region_start = pg_start;
		region_size = (pfn_cnt / HA_CHUNK) * HA_CHUNK;
		if (pfn_cnt % HA_CHUNK)
			region_size += HA_CHUNK;

		region_start = (pg_start / HA_CHUNK) * HA_CHUNK;

		rg_start = region_start;
		rg_sz = region_size;
	}

	if (do_hot_add)
		resp.page_count = process_hot_add(pg_start, pfn_cnt,
						rg_start, rg_sz);

	dm->num_pages_added += resp.page_count;
#endif


	if (resp.page_count > 0)
		resp.result = 1;
	else if (!do_hot_add)
		resp.result = 1;
	else
		resp.result = 0;

	if (!do_hot_add || (resp.page_count == 0))
		pr_info("Memory hot add failed\n");

	dm->state = DM_INITIALIZED;
	resp.hdr.trans_id = atomic_inc_return(&trans_id);
	vmbus_sendpacket(dm->dev->channel, &resp,
			sizeof(struct dm_hot_add_response),
			(unsigned long)NULL,
			VM_PKT_DATA_INBAND, 0);
}
