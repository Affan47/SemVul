show_channel(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct hid_device *hdev = container_of(dev, struct hid_device, dev);
	struct pk_device *pk = hid_get_drvdata(hdev);

	dbg_hid("pcmidi sysfs read channel=%u\n", pk->pm->midi_channel);

	return sprintf(buf, "%u (min:%u, max:%u)\n", pk->pm->midi_channel,
		PCMIDI_CHANNEL_MIN, PCMIDI_CHANNEL_MAX);
}
