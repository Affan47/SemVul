vxge_hw_ring_replenish(struct __vxge_hw_ring *ring)
{
	struct __vxge_hw_device *hldev;
	struct vxge_hw_ring_rxd_1 *rxd;
	enum vxge_hw_status status = VXGE_HW_OK;
	u8 offset = 0;
	struct __vxge_hw_ring_block *block;
	u8 i, iob_off;

	vxge_trace();

	hldev = ring->vpathh->hldev;


	for (i = 0; i < ARRAY_SIZE(ring->iobuf); i++) {
		ring->iobuf[i] = alloc_iob(VXGE_LL_MAX_FRAME_SIZE(hldev->vdev));
		if (!ring->iobuf[i]) {
			while (i) {
				free_iob(ring->iobuf[--i]);
				ring->iobuf[i] = NULL;
			}
			status = VXGE_HW_ERR_OUT_OF_MEMORY;
			goto iobuf_err;
		}
	}

	for (offset = 0; offset < VXGE_HW_MAX_RXDS_PER_BLOCK_1; offset++) {

		rxd = &ring->rxdl->rxd[offset];
		if (offset == (VXGE_HW_MAX_RXDS_PER_BLOCK_1 - 1))
			iob_off = VXGE_HW_RING_BUF_PER_BLOCK;
		else
			iob_off = offset % ring->buf_per_block;

		rxd->control_0 = rxd->control_1 = 0;
		vxge_hw_ring_rxd_1b_set(rxd, ring->iobuf[iob_off],
				VXGE_LL_MAX_FRAME_SIZE(hldev->vdev));

		vxge_hw_ring_rxd_post(ring, rxd);
	}

	block = ring->rxdl;
	block->reserved_2_pNext_RxD_block = (unsigned long) block;
	block->pNext_RxD_Blk_physical = (u64)virt_to_bus(block);

	ring->rxd_offset = 0;
iobuf_err:
	return status;
}
