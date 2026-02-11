hdspm_get_sync_in_sample_rate(struct hdspm *hdspm)
{
	int status;

	if (hdspm->tco) {
		switch (hdspm->io_type) {
		case RayDAT:
		case AIO:
			status = hdspm_read(hdspm, HDSPM_RD_STATUS_2);
			return (status >> 12) & 0xF;
			break;
		default:
			break;
		}
	}

	return 0;
}
