updatePrefix(SPtr<TDUID> duid , SPtr<TIPv6Addr> addr,
                            int iface, unsigned long IAID, unsigned long T1, unsigned long T2,
                            SPtr<TIPv6Addr> prefix, unsigned long pref, unsigned long valid,
                            int length, bool quiet)
{

    SPtr <TAddrClient> client;
    this->firstClient();
    while ( client = this->getClient() ) {
        if ( (*client->getDUID()) == (*duid) )
            break;
    }
    if (!client) {
        Log(Error) << "Unable to update prefix " << prefix->getPlain() << "/" << (int)length << ": DUID=" << duid->getPlain() << " not found." << LogEnd;
        return false;
    }

    return updatePrefix(client, duid, addr, iface, IAID, T1, T2, prefix, pref, valid, length, quiet);
}
