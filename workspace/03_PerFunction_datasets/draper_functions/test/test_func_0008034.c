getMem(n)
Int n; {
    Addr newAddr = addrHw;
    addrHw += n;
#if WANT_FIXED_SIZE_TABLES
    if (addrHw>=NUM_ADDRS) {
	ERRMSG(0) "Program code storage space exhausted"
	EEND;
    }
#else
    while (addrHw>=(Int)(dynMemory->maxIdx)) {
	growMemory();
    }
#endif
    return newAddr;
}
