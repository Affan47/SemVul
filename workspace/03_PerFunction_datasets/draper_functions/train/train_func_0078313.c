ata_eh_speed_down_verdict(struct ata_device *dev)
{
	const u64 j5mins = 5LLU * 60 * HZ, j10mins = 10LLU * 60 * HZ;
	u64 j64 = get_jiffies_64();
	struct speed_down_verdict_arg arg;
	unsigned int verdict = 0;


	memset(&arg, 0, sizeof(arg));
	arg.since = j64 - min(j64, j5mins);
	ata_ering_map(&dev->ering, speed_down_verdict_cb, &arg);

	if (arg.nr_errors[ATA_ECAT_DUBIOUS_ATA_BUS] +
	    arg.nr_errors[ATA_ECAT_DUBIOUS_TOUT_HSM] > 1)
		verdict |= ATA_EH_SPDN_SPEED_DOWN |
			ATA_EH_SPDN_FALLBACK_TO_PIO | ATA_EH_SPDN_KEEP_ERRORS;

	if (arg.nr_errors[ATA_ECAT_DUBIOUS_TOUT_HSM] +
	    arg.nr_errors[ATA_ECAT_DUBIOUS_UNK_DEV] > 1)
		verdict |= ATA_EH_SPDN_NCQ_OFF | ATA_EH_SPDN_KEEP_ERRORS;

	if (arg.nr_errors[ATA_ECAT_ATA_BUS] +
	    arg.nr_errors[ATA_ECAT_TOUT_HSM] +
	    arg.nr_errors[ATA_ECAT_UNK_DEV] > 6)
		verdict |= ATA_EH_SPDN_FALLBACK_TO_PIO;


	memset(&arg, 0, sizeof(arg));
	arg.since = j64 - min(j64, j10mins);
	ata_ering_map(&dev->ering, speed_down_verdict_cb, &arg);

	if (arg.nr_errors[ATA_ECAT_TOUT_HSM] +
	    arg.nr_errors[ATA_ECAT_UNK_DEV] > 3)
		verdict |= ATA_EH_SPDN_NCQ_OFF;

	if (arg.nr_errors[ATA_ECAT_ATA_BUS] +
	    arg.nr_errors[ATA_ECAT_TOUT_HSM] > 3 ||
	    arg.nr_errors[ATA_ECAT_UNK_DEV] > 6)
		verdict |= ATA_EH_SPDN_SPEED_DOWN;

	return verdict;
}
