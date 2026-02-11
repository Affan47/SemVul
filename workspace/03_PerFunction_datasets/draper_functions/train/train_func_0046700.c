fw_domain_wait_ack_clear(const struct intel_uncore_forcewake_domain *d)
{
	if (wait_for_atomic((__raw_i915_read32(d->i915, d->reg_ack) &
			     FORCEWAKE_KERNEL) == 0,
			    FORCEWAKE_ACK_TIMEOUT_MS))
		DRM_ERROR("%s: timed out waiting for forcewake ack to clear.\n",
			  intel_uncore_forcewake_domain_to_str(d->id));
}
