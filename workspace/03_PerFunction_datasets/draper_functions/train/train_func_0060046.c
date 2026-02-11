read(hsStream* S) {
    fContents = S->readByte();
    if (fContents & kHasServerName) {
        unsigned short len = S->readShort();
        fServerName = S->readStr(len);
    }
    if (fContents & kHasServerType)
        fServerType = S->readByte();
    if (fContents & kHasServerAddr) {
        unsigned short len = S->readShort();
        fServerAddr = S->readStr(len);
    }
    if (fContents & kHasServerPort)
        fServerPort = S->readShort();
    if (fContents & kHasServerGuid)
        fServerGuid.read(S);
}
