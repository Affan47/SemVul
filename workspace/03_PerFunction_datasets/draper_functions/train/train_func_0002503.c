ompi_btl_usnic_ack_send(
    ompi_btl_usnic_module_t *module,
    ompi_btl_usnic_endpoint_t *endpoint)
{
    ompi_btl_usnic_ack_segment_t *ack;
#if MSGDEBUG1
    uint8_t mac[6];
    char src_mac[32];
    char dest_mac[32];
#endif


    ack = ompi_btl_usnic_ack_segment_alloc(module);
    if (OPAL_UNLIKELY(NULL == ack)) {
        opal_output(0, "====================== No frag for sending the ACK -- skipped");
        abort();
    }


    ack->ss_base.us_btl_header->ack_seq =
        endpoint->endpoint_next_contig_seq_to_recv - 1;

    ack->ss_base.us_sg_entry[0].length =
        sizeof(ompi_btl_usnic_btl_header_t);

#if MSGDEBUG1
    memset(src_mac, 0, sizeof(src_mac));
    memset(dest_mac, 0, sizeof(dest_mac));
    ompi_btl_usnic_sprintf_mac(src_mac, module->if_mac);
    ompi_btl_usnic_gid_to_mac(&endpoint->endpoint_remote_addr.gid, mac);
    ompi_btl_usnic_sprintf_mac(dest_mac, mac);

    opal_output(0, "--> Sending ACK, sg_entry length %d, seq %" UDSEQ " to %s, qp %u",
                ack->ss_base.us_sg_entry[0].length,
                ack->ss_base.us_btl_header->ack_seq, dest_mac,
                endpoint->endpoint_remote_addr.qp_num[ack->ss_channel]);
#endif


    ompi_btl_usnic_post_segment(module, endpoint, ack);


    ++module->stats.num_ack_sends;

    return;
}
