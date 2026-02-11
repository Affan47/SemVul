enet_protocol_remove_sent_unreliable_commands (ENetPeer * peer)
{
    ENetOutgoingCommand * outgoingCommand;

    while (enet_list_empty (& peer -> sentUnreliableCommands) == 0)
    {
        outgoingCommand = (ENetOutgoingCommand *) enet_list_front (& peer -> sentUnreliableCommands);

        enet_list_remove (& outgoingCommand -> outgoingCommandList);

        if (outgoingCommand -> packet != NULL)
        {
           -- outgoingCommand -> packet -> referenceCount;

           if (outgoingCommand -> packet -> referenceCount == 0)
             enet_packet_destroy (outgoingCommand -> packet);
        }

        enet_free (outgoingCommand);
    }
}
