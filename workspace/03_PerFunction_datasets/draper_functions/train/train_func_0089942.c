initKnownChips(void)
{
	int nr, count = 1;
	const sensors_chip_name *name;


	nr = 0;
	while ((name = sensors_get_detected_chips(NULL, &nr)))
		count++;


	knownChips = calloc(count, sizeof(ChipDescriptor));
	if (!knownChips)
		return 1;


	count = 0;
	nr = 0;
	while ((name = sensors_get_detected_chips(NULL, &nr))) {
		knownChips[count].name = name;
		if ((knownChips[count].features = generateChipFeatures(name)))
			count++;
	}

	return 0;
}
