FindFixed (CNet*& nw, CNet* end) {
    for (nw = nw->Next(); nw != end; nw = nw->Next()) {
        CCnxn* c = nw->Cnxn();

        if (c->_lbConn->GetMobility() == Fixed) {
            return c->_lbConn;

        } else if (c->_rtConn->GetMobility() == Fixed) {
            return c->_rtConn;
        }
    }
    return nil;
}
