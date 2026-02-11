getPrefTimeout() {
    unsigned long ts = ULONG_MAX;

    SPtr<TAddrAddr> ptr;
    this->AddrLst.first();

    while (ptr = this->AddrLst.get() ) {
        if (ts > ptr->getPrefTimeout())
            ts = ptr->getPrefTimeout();
    }
    return ts;
}
