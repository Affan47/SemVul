intel_lrc_irq_handler(struct intel_engine_cs *ring)
{
	struct drm_i915_private *dev_priv = ring->dev->dev_private;
	u32 status_pointer;
	u8 read_pointer;
	u8 write_pointer;
	u32 status = 0;
	u32 status_id;
	u32 submit_contexts = 0;

	status_pointer = I915_READ(RING_CONTEXT_STATUS_PTR(ring));

	read_pointer = ring->next_context_status_buffer;
	write_pointer = status_pointer & GEN8_CSB_PTR_MASK;
	if (read_pointer > write_pointer)
		write_pointer += GEN8_CSB_ENTRIES;

	spin_lock(&ring->execlist_lock);

	while (read_pointer < write_pointer) {
		read_pointer++;
		status = I915_READ(RING_CONTEXT_STATUS_BUF_LO(ring, read_pointer % GEN8_CSB_ENTRIES));
		status_id = I915_READ(RING_CONTEXT_STATUS_BUF_HI(ring, read_pointer % GEN8_CSB_ENTRIES));

		if (status & GEN8_CTX_STATUS_IDLE_ACTIVE)
			continue;

		if (status & GEN8_CTX_STATUS_PREEMPTED) {
			if (status & GEN8_CTX_STATUS_LITE_RESTORE) {
				if (execlists_check_remove_request(ring, status_id))
					WARN(1, "Lite Restored request removed from queue\n");
			} else
				WARN(1, "Preemption without Lite Restore\n");
		}

		 if ((status & GEN8_CTX_STATUS_ACTIVE_IDLE) ||
		     (status & GEN8_CTX_STATUS_ELEMENT_SWITCH)) {
			if (execlists_check_remove_request(ring, status_id))
				submit_contexts++;
		}
	}

	if (disable_lite_restore_wa(ring)) {

		if ((status & GEN8_CTX_STATUS_ACTIVE_IDLE) &&
		    (submit_contexts != 0))
			execlists_context_unqueue(ring);
	} else if (submit_contexts != 0) {
		execlists_context_unqueue(ring);
	}

	spin_unlock(&ring->execlist_lock);

	WARN(submit_contexts > 2, "More than two context complete events?\n");
	ring->next_context_status_buffer = write_pointer % GEN8_CSB_ENTRIES;

	I915_WRITE(RING_CONTEXT_STATUS_PTR(ring),
		   _MASKED_FIELD(GEN8_CSB_PTR_MASK << 8,
				 ((u32)ring->next_context_status_buffer &
				  GEN8_CSB_PTR_MASK) << 8));
}
