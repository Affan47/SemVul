si_pmu_fast_pwrup_delay(struct si_pub *sih)
{
	uint delay = PMU_MAX_TRANSITION_DLY;

	switch (ai_get_chip_id(sih)) {
	case BCMA_CHIP_ID_BCM43224:
	case BCMA_CHIP_ID_BCM43225:
	case BCMA_CHIP_ID_BCM4313:
		delay = 3700;
		break;
	default:
		break;
	}

	return (u16) delay;
}
