enet_protocol_receive_incoming_commands (ENetHost * host, ENetEvent * event)
{
    for (;;)
    {
       int receivedLength;
       ENetBuffer buffer;

       buffer.data = host -> packetData [0];
       buffer.dataLength = sizeof (host -> packetData [0]);

       receivedLength = enet_socket_receive (host -> socket,
                                             & host -> receivedAddress,
                                             & buffer,
                                             1);

       if (receivedLength < 0)
         return -1;

       if (receivedLength == 0)
         return 0;

       host -> receivedData = host -> packetData [0];
       host -> receivedDataLength = receivedLength;

       host -> totalReceivedData += receivedLength;
       host -> totalReceivedPackets ++;

       switch (enet_protocol_handle_incoming_commands (host, event))
       {
       case 1:
          return 1;

       case -1:
          return -1;

       default:
          break;
       }
    }

    return -1;
}
