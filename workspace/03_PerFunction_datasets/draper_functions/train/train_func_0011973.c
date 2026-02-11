storeSelfRelay(char * buf, int relayDepth, ESrvIfaceIdOrder order)
{
    int offset = 0;
    if (relayDepth == this->Relays) {
	return storeSelf(buf);
    }
    buf[offset++] = RELAY_REPL_MSG;
    buf[offset++] = HopTbl[relayDepth];
    LinkAddrTbl[relayDepth]->storeSelf(buf+offset);
    PeerAddrTbl[relayDepth]->storeSelf(buf+offset+16);
    offset += 32;

    if (order == SRV_IFACE_ID_ORDER_BEFORE)
    {
	if (InterfaceIDTbl[relayDepth]) {
	    InterfaceIDTbl[relayDepth]->storeSelf(buf+offset);
	    offset += InterfaceIDTbl[relayDepth]->getSize();
	}
    }

    writeUint16((buf+offset), OPTION_RELAY_MSG);
    offset += sizeof(uint16_t);
    writeUint16((buf+offset), len[relayDepth]);
    offset += sizeof(uint16_t);

    offset += storeSelfRelay(buf+offset, relayDepth+1, order);

    if (order == SRV_IFACE_ID_ORDER_AFTER)
    {
	if (InterfaceIDTbl[relayDepth]) {
	    InterfaceIDTbl[relayDepth]->storeSelf(buf+offset);
	    offset += InterfaceIDTbl[relayDepth]->getSize();
	}
    }

    SPtr<TOptGeneric> gen;
    EchoListTbl[relayDepth].first();
    while (gen = EchoListTbl[relayDepth].get()) {
	Log(Debug) << "Echoing back option " << gen->getOptType() << ", length " << gen->getSize() << LogEnd;
	gen->storeSelf(buf+offset);
	offset += gen->getSize();
    }

    return offset;
}
