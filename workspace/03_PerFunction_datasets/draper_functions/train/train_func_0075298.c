NET_NewPacket(int initial_size)
{
    net_packet_t *packet;

    packet = (net_packet_t *) Z_Malloc(sizeof(net_packet_t), PU_STATIC, 0);

    if (initial_size == 0)
        initial_size = 256;

    packet->alloced = initial_size;
    packet->data = Z_Malloc(initial_size, PU_STATIC, 0);
    packet->len = 0;
    packet->pos = 0;

    total_packet_memory += sizeof(net_packet_t) + initial_size;


    return packet;
}
