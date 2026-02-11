doKnownChip(const sensors_chip_name *chip,
		       const ChipDescriptor *descriptor, int action)
{
	const FeatureDescriptor *features = descriptor->features;
	int i, ret = 0;

	if (action == DO_READ) {
		ret = idChip(chip);
		if (ret)
			return ret;
	}

	for (i = 0; features[i].format; i++) {
		ret = do_features(chip, features + i, action);
		if (ret == -1)
			break;
	}

	return ret;
}
