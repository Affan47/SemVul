destroy_instance(AFPacketInstance *instance)
{
    unsigned int ringsize;
    struct tpacket_req req;

    if (instance)
    {
        if (instance->fd != -1)
        {

            if (instance->rx_ring.entries)
            {
                free(instance->rx_ring.entries);
                instance->rx_ring.entries = NULL;
            }

            if (instance->tx_ring.entries)
            {
                free(instance->tx_ring.entries);
                instance->tx_ring.entries = NULL;
            }

            if (instance->buffer != MAP_FAILED)
            {
                ringsize = instance->rx_ring.size + instance->tx_ring.size;
                munmap(instance->buffer, ringsize);
                instance->buffer = MAP_FAILED;
            }

            memset(&req, 0, sizeof(req));
            setsockopt(instance->fd, SOL_PACKET, PACKET_RX_RING, (void *) &req, sizeof(req));
            setsockopt(instance->fd, SOL_PACKET, PACKET_TX_RING, (void *) &req, sizeof(req));
            close(instance->fd);
        }
        if (instance->name)
        {
            free(instance->name);
            instance->name = NULL;
        }
        free(instance);
    }
}
