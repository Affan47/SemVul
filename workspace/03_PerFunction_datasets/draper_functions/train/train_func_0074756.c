saa7164_unitid_name(struct saa7164_dev *dev, u8 unitid)
{
	char *undefed = "UNDEFINED";
	char *bridge = "BRIDGE";
	struct saa7164_unit *unit;
	int i;

	if (unitid == 0)
		return bridge;

	for (i = 0; i < SAA7164_MAX_UNITS; i++) {
		unit = &saa7164_boards[dev->board].unit[i];

		if (unit->type == SAA7164_UNIT_UNDEFINED)
			continue;

		if (unitid == unit->id)
				return unit->name;
	}

	return undefed;
}
