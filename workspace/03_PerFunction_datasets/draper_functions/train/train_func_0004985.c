enet_peer_reset_outgoing_commands (ENetList * queue)
{
    ENetOutgoingCommand * outgoingCommand;

    while (enet_list_empty (queue) == 0)
    {
       outgoingCommand = (ENetOutgoingCommand *) enet_list_remove (enet_list_begin (queue));

       if (outgoingCommand -> packet != NULL)
       {
          -- outgoingCommand -> packet -> referenceCount;

          if (outgoingCommand -> packet -> referenceCount == 0)
            enet_packet_destroy (outgoingCommand -> packet);
       }

       enet_free (outgoingCommand);
    }
}
