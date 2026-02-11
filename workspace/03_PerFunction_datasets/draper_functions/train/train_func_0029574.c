snic_update_abort_stats(struct snic *snic, u8 cmpl_stat)
{
	struct snic_abort_stats *abt_stats = &snic->s_stats.abts;

	SNIC_SCSI_DBG(snic->shost, "Updating Abort stats.\n");

	switch (cmpl_stat) {
	case  SNIC_STAT_IO_SUCCESS:
		break;

	case SNIC_STAT_TIMEOUT:
		atomic64_inc(&abt_stats->fw_tmo);
		break;

	case SNIC_STAT_IO_NOT_FOUND:
		atomic64_inc(&abt_stats->io_not_found);
		break;

	default:
		atomic64_inc(&abt_stats->fail);
		break;
	}
}
