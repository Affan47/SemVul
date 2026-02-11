getSize() {
    int pktsize=0;
    TOptList::iterator opt;
    for (opt = Options.begin(); opt!=Options.end(); ++opt)
    {
	pktsize += (*opt)->getSize();
    }
    return pktsize + MIN_RELAYFORW_LEN;
}
