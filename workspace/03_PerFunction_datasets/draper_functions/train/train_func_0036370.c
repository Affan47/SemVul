NET_SV_RecvPacket(net_addr_t **addr, net_packet_t **packet)
{
    net_packet_t *popped;

    popped = QueuePop(&server_queue);

    if (popped != NULL)
    {
        *packet = popped;
        *addr = &server_addr;
        server_addr.module = &net_loop_server_module;

        return true;
    }

    return false;
}
