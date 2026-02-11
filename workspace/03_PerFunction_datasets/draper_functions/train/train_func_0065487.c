Close(tint channel) {
    struct evbuffer *evb = evbuffer_new();
    AddHdr(evb, mymac, peer_mac);
    evbuffer_add_32be(evb, channel);
    evbuffer_add_8(evb, SWIFT_ETH_CLOSE);
    evbuffer_add_8(evb, SWIFT_ETH_END);
    dprintf("%s #%u +close\n", tintstr(), my_channel);
    msgs.push_back(evb);

}
