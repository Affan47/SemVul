enet_packet_create (const void * data, size_t dataLength, enet_uint32 flags)
{
    ENetPacket * packet = (ENetPacket *) enet_malloc (sizeof (ENetPacket));

    packet -> data = (enet_uint8 *) enet_malloc (dataLength);

    if (data != NULL)
      memcpy (packet -> data, data, dataLength);

    packet -> referenceCount = 0;
    packet -> flags = flags;
    packet -> dataLength = dataLength;

    return packet;
}
