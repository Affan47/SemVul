semaphore_passed(struct intel_engine_cs *ring)
{
	struct drm_i915_private *dev_priv = ring->dev->dev_private;
	struct intel_engine_cs *signaller;
	u32 seqno;

	ring->hangcheck.deadlock++;

	signaller = semaphore_waits_for(ring, &seqno);
	if (signaller == NULL)
		return -1;


	if (signaller->hangcheck.deadlock >= I915_NUM_RINGS)
		return -1;

	if (i915_seqno_passed(signaller->get_seqno(signaller, false), seqno))
		return 1;


	if (I915_READ_CTL(signaller) & RING_WAIT_SEMAPHORE &&
	    semaphore_passed(signaller) < 0)
		return -1;

	return 0;
}
