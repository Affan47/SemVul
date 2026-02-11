doChip(const sensors_chip_name *chip, int action)
{
	int ret = 0;
	if (action == DO_SET) {
		ret = setChip(chip);
	} else {
		int index0, chipindex = -1;
		for (index0 = 0; knownChips[index0].features; ++index0) {


			if (knownChips[index0].name == chip) {
				chipindex = index0;
				break;
			}
		}

		if (chipindex >= 0) {
			ret = doKnownChip(chip, &knownChips[chipindex],
					  action);
		}
	}
	return ret;
}
