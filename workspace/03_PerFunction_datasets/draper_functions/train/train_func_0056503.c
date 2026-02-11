DeletePeerInfo (Connector* c, ConnInfo* info) {
    Iterator i;

    for (info->First(i); !info->Done(i); info->First(i)) {
        DeletePeerInfo(c, info, info->GetInfo(i)->_peer);
    }
}
