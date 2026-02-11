fc_get_host_stats(struct Scsi_Host *shost)
{
	struct fc_host_statistics *fc_stats;
	struct fc_lport *lport = shost_priv(shost);
	struct timespec v0, v1;
	unsigned int cpu;
	u64 fcp_in_bytes = 0;
	u64 fcp_out_bytes = 0;

	fc_stats = &lport->host_stats;
	memset(fc_stats, 0, sizeof(struct fc_host_statistics));

	jiffies_to_timespec(jiffies, &v0);
	jiffies_to_timespec(lport->boot_time, &v1);
	fc_stats->seconds_since_last_reset = (v0.tv_sec - v1.tv_sec);

	for_each_possible_cpu(cpu) {
		struct fc_stats *stats;

		stats = per_cpu_ptr(lport->stats, cpu);

		fc_stats->tx_frames += stats->TxFrames;
		fc_stats->tx_words += stats->TxWords;
		fc_stats->rx_frames += stats->RxFrames;
		fc_stats->rx_words += stats->RxWords;
		fc_stats->error_frames += stats->ErrorFrames;
		fc_stats->invalid_crc_count += stats->InvalidCRCCount;
		fc_stats->fcp_input_requests += stats->InputRequests;
		fc_stats->fcp_output_requests += stats->OutputRequests;
		fc_stats->fcp_control_requests += stats->ControlRequests;
		fcp_in_bytes += stats->InputBytes;
		fcp_out_bytes += stats->OutputBytes;
		fc_stats->fcp_packet_alloc_failures += stats->FcpPktAllocFails;
		fc_stats->fcp_packet_aborts += stats->FcpPktAborts;
		fc_stats->fcp_frame_alloc_failures += stats->FcpFrameAllocFails;
		fc_stats->link_failure_count += stats->LinkFailureCount;
	}
	fc_stats->fcp_input_megabytes = div_u64(fcp_in_bytes, 1000000);
	fc_stats->fcp_output_megabytes = div_u64(fcp_out_bytes, 1000000);
	fc_stats->lip_count = -1;
	fc_stats->nos_count = -1;
	fc_stats->loss_of_sync_count = -1;
	fc_stats->loss_of_signal_count = -1;
	fc_stats->prim_seq_protocol_err_count = -1;
	fc_stats->dumped_frames = -1;


	fc_exch_update_stats(lport);

	return fc_stats;
}
