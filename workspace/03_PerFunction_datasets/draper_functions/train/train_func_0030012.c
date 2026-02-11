si4713_set_mute(struct si4713_device *sdev, u16 mute)
{
	int rval = 0;

	mute = set_mute(mute);

	if (sdev->power_state)
		rval = si4713_write_property(sdev,
				SI4713_TX_LINE_INPUT_MUTE, mute);

	return rval;
}
