writeCMER(dMessage* dm)
{
    logger(L_DBG, "[DS]: Send CMER");

    SingleList* list = _connections;
    while (list) {

        ConnectInfo* peer = (ConnectInfo*) list->data;

        if (peer->state == PEER_CONNECTED &&
            (peer->mode == CLIENT_RFCOMM || peer->mode == CLIENT_AT)) {

            int fd = _peerHandlers[peer->mode].descriptor(peer);
            if (fd >= 0) {
                sendCMER(fd, dm->size);
            }
        }
        list = listSingleNext(list);
    }
    return EXIT_OK;
}
