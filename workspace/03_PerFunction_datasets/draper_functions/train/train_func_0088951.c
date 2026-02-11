enet_protocol_dispatch_state (ENetHost * host, ENetPeer * peer, ENetPeerState state)
{
    enet_protocol_change_state (host, peer, state);

    if (! peer -> needsDispatch)
    {
       enet_list_insert (enet_list_end (& host -> dispatchQueue), & peer -> dispatchList);

       peer -> needsDispatch = 1;
    }
}
