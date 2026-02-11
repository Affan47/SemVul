semaphore_waits_for(struct intel_engine_cs *ring, u32 *seqno)
{
	struct drm_i915_private *dev_priv = ring->dev->dev_private;
	u32 cmd, ipehr, head;
	u64 offset = 0;
	int i, backwards;


	if (ring->buffer == NULL)
		return NULL;

	ipehr = I915_READ(RING_IPEHR(ring->mmio_base));
	if (!ipehr_is_semaphore_wait(ring->dev, ipehr))
		return NULL;


	head = I915_READ_HEAD(ring) & HEAD_ADDR;
	backwards = (INTEL_INFO(ring->dev)->gen >= 8) ? 5 : 4;

	for (i = backwards; i; --i) {


		head &= ring->buffer->size - 1;


		cmd = ioread32(ring->buffer->virtual_start + head);
		if (cmd == ipehr)
			break;

		head -= 4;
	}

	if (!i)
		return NULL;

	*seqno = ioread32(ring->buffer->virtual_start + head + 4) + 1;
	if (INTEL_INFO(ring->dev)->gen >= 8) {
		offset = ioread32(ring->buffer->virtual_start + head + 12);
		offset <<= 32;
		offset = ioread32(ring->buffer->virtual_start + head + 8);
	}
	return semaphore_wait_to_signaller_ring(ring, ipehr, offset);
}
