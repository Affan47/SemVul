i915_gem_check_wedge(unsigned reset_counter, bool interruptible)
{
	if (__i915_terminally_wedged(reset_counter))
		return -EIO;

	if (__i915_reset_in_progress(reset_counter)) {


		if (!interruptible)
			return -EIO;

		return -EAGAIN;
	}

	return 0;
}
