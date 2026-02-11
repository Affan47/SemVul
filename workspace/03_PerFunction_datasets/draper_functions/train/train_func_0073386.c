recvCmd(uint32_t op)
{
    switch (op) {
    case HANDSHAKE:
        setupRecvData(1, HANDSHAKE);
        break;

    case PROTO_ERANGE:
        doFailure("Got list range error from Metaserver");
        break;

    case LIST_RESP:
        setupRecvData(2, LIST_RESP);
        break;

    default:
        doFailure("Unknown Meta server command");
    }
}
