Disconnect (Connector* c) {
    CSolverInfo* csinfo = c->_csinfo;

    if (csinfo != nil) {
        DeleteCnxnsTo(c, csinfo->_hinfo->GetNetwork(), _hnets);
        DeleteCnxnsTo(c, csinfo->_vinfo->GetNetwork(), _vnets);
        DeletePeerInfo(c, csinfo->_hinfo);
        DeletePeerInfo(c, csinfo->_vinfo);

        delete csinfo;
        c->_csinfo = nil;
    }
}
