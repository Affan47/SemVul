vxge_hw_ring_rxd_reserve(struct __vxge_hw_ring *ring,
	void **rxdh)
{
	enum vxge_hw_status status;
	struct __vxge_hw_channel *channel;

	channel = &ring->channel;

	status = vxge_hw_channel_dtr_alloc(channel, rxdh);

	if (status == VXGE_HW_OK) {
		struct vxge_hw_ring_rxd_1 *rxdp =
			(struct vxge_hw_ring_rxd_1 *)*rxdh;

		rxdp->control_0	= rxdp->control_1 = 0;
	}

	return status;
}
