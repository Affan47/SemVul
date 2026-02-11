enet_peer_setup_outgoing_command (ENetPeer * peer, ENetOutgoingCommand * outgoingCommand)
{
    ENetChannel * channel = & peer -> channels [outgoingCommand -> command.header.channelID];

    peer -> outgoingDataTotal += enet_protocol_command_size (outgoingCommand -> command.header.command) + outgoingCommand -> fragmentLength;

    if (outgoingCommand -> command.header.channelID == 0xFF)
    {
       ++ peer -> outgoingReliableSequenceNumber;

       outgoingCommand -> reliableSequenceNumber = peer -> outgoingReliableSequenceNumber;
       outgoingCommand -> unreliableSequenceNumber = 0;
    }
    else
    if (outgoingCommand -> command.header.command & ENET_PROTOCOL_COMMAND_FLAG_ACKNOWLEDGE)
    {
       ++ channel -> outgoingReliableSequenceNumber;
       channel -> outgoingUnreliableSequenceNumber = 0;

       outgoingCommand -> reliableSequenceNumber = channel -> outgoingReliableSequenceNumber;
       outgoingCommand -> unreliableSequenceNumber = 0;
    }
    else
    if (outgoingCommand -> command.header.command & ENET_PROTOCOL_COMMAND_FLAG_UNSEQUENCED)
    {
       ++ peer -> outgoingUnsequencedGroup;

       outgoingCommand -> reliableSequenceNumber = 0;
       outgoingCommand -> unreliableSequenceNumber = 0;
    }
    else
    {
       if (outgoingCommand -> fragmentOffset == 0)
         ++ channel -> outgoingUnreliableSequenceNumber;

       outgoingCommand -> reliableSequenceNumber = channel -> outgoingReliableSequenceNumber;
       outgoingCommand -> unreliableSequenceNumber = channel -> outgoingUnreliableSequenceNumber;
    }

    outgoingCommand -> sendAttempts = 0;
    outgoingCommand -> sentTime = 0;
    outgoingCommand -> roundTripTimeout = 0;
    outgoingCommand -> roundTripTimeoutLimit = 0;
    outgoingCommand -> command.header.reliableSequenceNumber = ENET_HOST_TO_NET_16 (outgoingCommand -> reliableSequenceNumber);

    switch (outgoingCommand -> command.header.command & ENET_PROTOCOL_COMMAND_MASK)
    {
    case ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE:
        outgoingCommand -> command.sendUnreliable.unreliableSequenceNumber = ENET_HOST_TO_NET_16 (outgoingCommand -> unreliableSequenceNumber);
        break;

    case ENET_PROTOCOL_COMMAND_SEND_UNSEQUENCED:
        outgoingCommand -> command.sendUnsequenced.unsequencedGroup = ENET_HOST_TO_NET_16 (peer -> outgoingUnsequencedGroup);
        break;

    default:
        break;
    }

    if (outgoingCommand -> command.header.command & ENET_PROTOCOL_COMMAND_FLAG_ACKNOWLEDGE)
      enet_list_insert (enet_list_end (& peer -> outgoingReliableCommands), outgoingCommand);
    else
      enet_list_insert (enet_list_end (& peer -> outgoingUnreliableCommands), outgoingCommand);
}
