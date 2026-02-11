calculate_layout(AFPacket_Context_t *afpc, struct tpacket_req *layout, unsigned int tp_hdrlen, int order)
{
    unsigned int tp_hdrlen_sll, netoff, frames_per_block;


    tp_hdrlen_sll = TPACKET_ALIGN(tp_hdrlen) + sizeof(struct sockaddr_ll);
    netoff = TPACKET_ALIGN(tp_hdrlen_sll + ETH_HLEN) + VLAN_TAG_LEN;
    layout->tp_frame_size = TPACKET_ALIGN(netoff - ETH_HLEN + afpc->snaplen);
    layout->tp_block_size = getpagesize() << order;
    while (layout->tp_block_size < layout->tp_frame_size)
        layout->tp_block_size <<= 1;
    frames_per_block = layout->tp_block_size / layout->tp_frame_size;
    if (frames_per_block == 0)
    {
        DPE(afpc->errbuf, "%s: Invalid frames per block (%u/%u) for %s",
                __FUNCTION__, layout->tp_block_size, layout->tp_frame_size, afpc->device);
        return DAQ_ERROR;
    }


    layout->tp_frame_nr = afpc->size / layout->tp_frame_size;
    layout->tp_block_nr = layout->tp_frame_nr / frames_per_block;

    layout->tp_frame_nr = layout->tp_block_nr * frames_per_block;
    if (afpc->debug)
    {
        printf("AFPacket Layout:\n");
        printf("  Frame Size: %u\n", layout->tp_frame_size);
        printf("  Frames:     %u\n", layout->tp_frame_nr);
        printf("  Block Size: %u (Order %d)\n", layout->tp_block_size, order);
        printf("  Blocks:     %u\n", layout->tp_block_nr);
    }

    return DAQ_SUCCESS;
}
