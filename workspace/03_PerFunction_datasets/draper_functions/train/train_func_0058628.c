enet_peer_dispatch_incoming_unreliable_commands (ENetPeer * peer, ENetChannel * channel)
{
    ENetListIterator currentCommand;

    for (currentCommand = enet_list_begin (& channel -> incomingUnreliableCommands);
         currentCommand != enet_list_end (& channel -> incomingUnreliableCommands);
         currentCommand = enet_list_next (currentCommand))
    {
       ENetIncomingCommand * incomingCommand = (ENetIncomingCommand *) currentCommand;

       if ((incomingCommand -> command.header.command & ENET_PROTOCOL_COMMAND_MASK) == ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE &&
           incomingCommand -> reliableSequenceNumber != channel -> incomingReliableSequenceNumber)
         break;
    }

    if (currentCommand == enet_list_begin (& channel -> incomingUnreliableCommands))
      return;

    enet_list_move (enet_list_end (& peer -> dispatchedCommands), enet_list_begin (& channel -> incomingUnreliableCommands), enet_list_previous (currentCommand));

    if (! peer -> needsDispatch)
    {
       enet_list_insert (enet_list_end (& peer -> host -> dispatchQueue), & peer -> dispatchList);

       peer -> needsDispatch = 1;
    }
}
