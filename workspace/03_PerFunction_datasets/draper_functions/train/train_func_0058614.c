ssb_pmu_get_controlclock(struct ssb_chipcommon *cc)
{
	struct ssb_bus *bus = cc->dev->bus;

	switch (bus->chip_id) {
	case 0x5354:
		return 120000000;
	default:
		ssb_err("ERROR: PMU controlclock unknown for device %04X\n",
			bus->chip_id);
		return 0;
	}
}
