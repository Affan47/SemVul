ssb_device_disable(struct ssb_device *dev, u32 core_specific_flags)
{
	u32 reject, val;

	if (ssb_read32(dev, SSB_TMSLOW) & SSB_TMSLOW_RESET)
		return;

	reject = ssb_tmslow_reject_bitmask(dev);

	if (ssb_read32(dev, SSB_TMSLOW) & SSB_TMSLOW_CLOCK) {
		ssb_write32(dev, SSB_TMSLOW, reject | SSB_TMSLOW_CLOCK);
		ssb_wait_bits(dev, SSB_TMSLOW, reject, 1000, 1);
		ssb_wait_bits(dev, SSB_TMSHIGH, SSB_TMSHIGH_BUSY, 1000, 0);

		if (ssb_read32(dev, SSB_IDLOW) & SSB_IDLOW_INITIATOR) {
			val = ssb_read32(dev, SSB_IMSTATE);
			val |= SSB_IMSTATE_REJECT;
			ssb_write32(dev, SSB_IMSTATE, val);
			ssb_wait_bits(dev, SSB_IMSTATE, SSB_IMSTATE_BUSY, 1000,
				      0);
		}

		ssb_write32(dev, SSB_TMSLOW,
			SSB_TMSLOW_FGC | SSB_TMSLOW_CLOCK |
			reject | SSB_TMSLOW_RESET |
			core_specific_flags);
		ssb_flush_tmslow(dev);

		if (ssb_read32(dev, SSB_IDLOW) & SSB_IDLOW_INITIATOR) {
			val = ssb_read32(dev, SSB_IMSTATE);
			val &= ~SSB_IMSTATE_REJECT;
			ssb_write32(dev, SSB_IMSTATE, val);
		}
	}

	ssb_write32(dev, SSB_TMSLOW,
		    reject | SSB_TMSLOW_RESET |
		    core_specific_flags);
	ssb_flush_tmslow(dev);
}
