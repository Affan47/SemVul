DisconnectAll () {
    csolver->Disconnect(this);

    while (!_cnxns->IsEmpty()) {
        UList* r = _cnxns->First();
        Connector* conn = Conn(r);
        DisconnectMe(conn);
        _cnxns->Remove(r);
        delete r;
    }
}
