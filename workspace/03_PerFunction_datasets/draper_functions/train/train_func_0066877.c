wl1251_acx_mem_cfg(struct wl1251 *wl)
{
	struct wl1251_acx_config_memory *mem_conf;
	int ret, i;

	wl1251_debug(DEBUG_ACX, "acx mem cfg");

	mem_conf = kzalloc(sizeof(*mem_conf), GFP_KERNEL);
	if (!mem_conf)
		return -ENOMEM;


	mem_conf->mem_config.num_stations = cpu_to_le16(DEFAULT_NUM_STATIONS);
	mem_conf->mem_config.rx_mem_block_num = 35;
	mem_conf->mem_config.tx_min_mem_block_num = 64;
	mem_conf->mem_config.num_tx_queues = MAX_TX_QUEUES;
	mem_conf->mem_config.host_if_options = HOSTIF_PKT_RING;
	mem_conf->mem_config.num_ssid_profiles = 1;
	mem_conf->mem_config.debug_buffer_size =
		cpu_to_le16(TRACE_BUFFER_MAX_SIZE);


	mem_conf->rx_queue_config.dma_address = 0;
	mem_conf->rx_queue_config.num_descs = ACX_RX_DESC_DEF;
	mem_conf->rx_queue_config.priority = DEFAULT_RXQ_PRIORITY;
	mem_conf->rx_queue_config.type = DEFAULT_RXQ_TYPE;


	for (i = 0; i < MAX_TX_QUEUES; i++) {
		mem_conf->tx_queue_config[i].num_descs = ACX_TX_DESC_DEF;
		mem_conf->tx_queue_config[i].attributes = i;
	}

	ret = wl1251_cmd_configure(wl, ACX_MEM_CFG, mem_conf,
				   sizeof(*mem_conf));
	if (ret < 0) {
		wl1251_warning("wl1251 mem config failed: %d", ret);
		goto out;
	}

out:
	kfree(mem_conf);
	return ret;
}
