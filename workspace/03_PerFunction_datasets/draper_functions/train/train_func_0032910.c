addAddr(SPtr<TIPv6Addr> addr, unsigned long pref, unsigned long valid)
{
    SPtr<TAddrAddr> ptr = new TAddrAddr(addr, pref, valid);
    AddrLst.append(ptr);
    Tentative = TENTATIVE_UNKNOWN;
}
