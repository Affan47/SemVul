usnic_stats_reset(ompi_btl_usnic_module_t *module)
{
    int i;

    module->stats.num_total_sends =
        module->stats.num_resends =
        module->stats.num_chunk_sends =
        module->stats.num_frag_sends =
        module->stats.num_ack_recvs =

        module->stats.num_total_recvs =
        module->stats.num_unk_recvs =
        module->stats.num_dup_recvs =
        module->stats.num_oow_low_recvs =
        module->stats.num_oow_high_recvs =
        module->stats.num_frag_recvs =
        module->stats.num_chunk_recvs =
        module->stats.num_badfrag_recvs =
        module->stats.num_ack_sends =
        module->stats.num_recv_reposts =
        module->stats.num_crc_errors =

        module->stats.num_old_dup_acks =
        module->stats.num_dup_acks =
        module->stats.num_fast_retrans =
        module->stats.num_timeout_retrans =

        module->stats.max_sent_window_size =
        module->stats.max_rcvd_window_size =

        module->stats.pml_module_sends =
        module->stats.pml_send_callbacks =

        0;

    for (i=0; i<USNIC_NUM_CHANNELS; ++i) {
        module->mod_channels[i].num_channel_sends = 0;
    }
}
