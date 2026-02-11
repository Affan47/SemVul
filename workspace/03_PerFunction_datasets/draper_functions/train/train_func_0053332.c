prepareErrorAck(ZrtpPacketError* epkt) {
    if (epkt->getLength() < 4)
        sendInfo(ZrtpError, CriticalSWError * -1);
    else
        sendInfo(ZrtpError, epkt->getErrorCode() * -1);
    return &zrtpErrorAck;
}
