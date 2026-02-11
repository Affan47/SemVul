enet_protocol_send_acknowledgements (ENetHost * host, ENetPeer * peer)
{
    ENetProtocol * command = & host -> commands [host -> commandCount];
    ENetBuffer * buffer = & host -> buffers [host -> bufferCount];
    ENetAcknowledgement * acknowledgement;
    ENetListIterator currentAcknowledgement;

    currentAcknowledgement = enet_list_begin (& peer -> acknowledgements);

    while (currentAcknowledgement != enet_list_end (& peer -> acknowledgements))
    {
       if (command >= & host -> commands [sizeof (host -> commands) / sizeof (ENetProtocol)] ||
           buffer >= & host -> buffers [sizeof (host -> buffers) / sizeof (ENetBuffer)] ||
           peer -> mtu - host -> packetSize < sizeof (ENetProtocolAcknowledge))
       {
          host -> continueSending = 1;

          break;
       }

       acknowledgement = (ENetAcknowledgement *) currentAcknowledgement;

       currentAcknowledgement = enet_list_next (currentAcknowledgement);

       buffer -> data = command;
       buffer -> dataLength = sizeof (ENetProtocolAcknowledge);

       host -> packetSize += buffer -> dataLength;

       command -> header.command = ENET_PROTOCOL_COMMAND_ACKNOWLEDGE;
       command -> header.channelID = acknowledgement -> command.header.channelID;
       command -> acknowledge.receivedReliableSequenceNumber = ENET_HOST_TO_NET_16 (acknowledgement -> command.header.reliableSequenceNumber);
       command -> acknowledge.receivedSentTime = ENET_HOST_TO_NET_16 (acknowledgement -> sentTime);

       if ((acknowledgement -> command.header.command & ENET_PROTOCOL_COMMAND_MASK) == ENET_PROTOCOL_COMMAND_DISCONNECT)
         enet_protocol_dispatch_state (host, peer, ENET_PEER_STATE_ZOMBIE);

       enet_list_remove (& acknowledgement -> acknowledgementList);
       enet_free (acknowledgement);

       ++ command;
       ++ buffer;
    }

    host -> commandCount = command - host -> commands;
    host -> bufferCount = buffer - host -> buffers;
}
