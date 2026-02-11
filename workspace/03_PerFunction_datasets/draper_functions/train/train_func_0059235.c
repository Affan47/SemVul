handle_irq_beacon(struct b43legacy_wldev *dev)
{
	struct b43legacy_wl *wl = dev->wl;
	u32 cmd, beacon0_valid, beacon1_valid;

	if (!b43legacy_is_mode(wl, NL80211_IFTYPE_AP))
		return;


	dev->irq_mask &= ~B43legacy_IRQ_BEACON;

	cmd = b43legacy_read32(dev, B43legacy_MMIO_MACCMD);
	beacon0_valid = (cmd & B43legacy_MACCMD_BEACON0_VALID);
	beacon1_valid = (cmd & B43legacy_MACCMD_BEACON1_VALID);


	if (beacon0_valid && beacon1_valid) {
		b43legacy_write32(dev, B43legacy_MMIO_GEN_IRQ_REASON, B43legacy_IRQ_BEACON);
		dev->irq_mask |= B43legacy_IRQ_BEACON;
		return;
	}

	if (unlikely(wl->beacon_templates_virgin)) {


		wl->beacon_templates_virgin = false;
		b43legacy_upload_beacon0(dev);
		b43legacy_upload_beacon1(dev);
		cmd = b43legacy_read32(dev, B43legacy_MMIO_MACCMD);
		cmd |= B43legacy_MACCMD_BEACON0_VALID;
		b43legacy_write32(dev, B43legacy_MMIO_MACCMD, cmd);
	} else {
		if (!beacon0_valid) {
			b43legacy_upload_beacon0(dev);
			cmd = b43legacy_read32(dev, B43legacy_MMIO_MACCMD);
			cmd |= B43legacy_MACCMD_BEACON0_VALID;
			b43legacy_write32(dev, B43legacy_MMIO_MACCMD, cmd);
		} else if (!beacon1_valid) {
			b43legacy_upload_beacon1(dev);
			cmd = b43legacy_read32(dev, B43legacy_MMIO_MACCMD);
			cmd |= B43legacy_MACCMD_BEACON1_VALID;
			b43legacy_write32(dev, B43legacy_MMIO_MACCMD, cmd);
		}
	}
}
