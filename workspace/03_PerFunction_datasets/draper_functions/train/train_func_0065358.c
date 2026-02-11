__vxge_hw_ring_create(struct __vxge_hw_vpath_handle *vp,
		      struct vxge_hw_ring_attr *attr)
{
	enum vxge_hw_status status = VXGE_HW_OK;
	struct __vxge_hw_ring *ring;
	u32 ring_length;
	struct vxge_hw_ring_config *config;
	struct __vxge_hw_device *hldev;
	u32 vp_id;
	static const struct vxge_hw_mempool_cbs ring_mp_callback = {
		.item_func_alloc = __vxge_hw_ring_mempool_item_alloc,
	};

	if ((vp == NULL) || (attr == NULL)) {
		status = VXGE_HW_FAIL;
		goto exit;
	}

	hldev = vp->vpath->hldev;
	vp_id = vp->vpath->vp_id;

	config = &hldev->config.vp_config[vp_id].ring;

	ring_length = config->ring_blocks *
			vxge_hw_ring_rxds_per_block_get(config->buffer_mode);

	ring = (struct __vxge_hw_ring *)__vxge_hw_channel_allocate(vp,
						VXGE_HW_CHANNEL_TYPE_RING,
						ring_length,
						attr->per_rxd_space,
						attr->userdata);
	if (ring == NULL) {
		status = VXGE_HW_ERR_OUT_OF_MEMORY;
		goto exit;
	}

	vp->vpath->ringh = ring;
	ring->vp_id = vp_id;
	ring->vp_reg = vp->vpath->vp_reg;
	ring->common_reg = hldev->common_reg;
	ring->stats = &vp->vpath->sw_stats->ring_stats;
	ring->config = config;
	ring->callback = attr->callback;
	ring->rxd_init = attr->rxd_init;
	ring->rxd_term = attr->rxd_term;
	ring->buffer_mode = config->buffer_mode;
	ring->tim_rti_cfg1_saved = vp->vpath->tim_rti_cfg1_saved;
	ring->tim_rti_cfg3_saved = vp->vpath->tim_rti_cfg3_saved;
	ring->rxds_limit = config->rxds_limit;

	ring->rxd_size = vxge_hw_ring_rxd_size_get(config->buffer_mode);
	ring->rxd_priv_size =
		sizeof(struct __vxge_hw_ring_rxd_priv) + attr->per_rxd_space;
	ring->per_rxd_space = attr->per_rxd_space;

	ring->rxd_priv_size =
		((ring->rxd_priv_size + VXGE_CACHE_LINE_SIZE - 1) /
		VXGE_CACHE_LINE_SIZE) * VXGE_CACHE_LINE_SIZE;


	ring->rxds_per_block =
		vxge_hw_ring_rxds_per_block_get(config->buffer_mode);


	ring->rxdblock_priv_size = ring->rxd_priv_size * ring->rxds_per_block;
	ring->mempool = __vxge_hw_mempool_create(hldev,
				VXGE_HW_BLOCK_SIZE,
				VXGE_HW_BLOCK_SIZE,
				ring->rxdblock_priv_size,
				ring->config->ring_blocks,
				ring->config->ring_blocks,
				&ring_mp_callback,
				ring);
	if (ring->mempool == NULL) {
		__vxge_hw_ring_delete(vp);
		return VXGE_HW_ERR_OUT_OF_MEMORY;
	}

	status = __vxge_hw_channel_initialize(&ring->channel);
	if (status != VXGE_HW_OK) {
		__vxge_hw_ring_delete(vp);
		goto exit;
	}


	if (ring->rxd_init) {
		status = vxge_hw_ring_replenish(ring);
		if (status != VXGE_HW_OK) {
			__vxge_hw_ring_delete(vp);
			goto exit;
		}
	}


	ring->stats->common_stats.usage_cnt = 0;
exit:
	return status;
}
