pcap_daq_inject(void *handle, const DAQ_PktHdr_t *hdr, const uint8_t *packet_data, uint32_t len, int reverse)
{
    Pcap_Context_t *context = (Pcap_Context_t *) handle;

    if (pcap_inject(context->handle, packet_data, len) < 0)
    {
        DPE(context->errbuf, "%s", pcap_geterr(context->handle));
        return DAQ_ERROR;
    }

    context->stats.packets_injected++;
    return DAQ_SUCCESS;
}
