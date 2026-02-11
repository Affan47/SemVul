RxTry(RxNode *rx, const char *s) {
    int fl = flags;
    rex = s;
    for (int i = 0; i < NSEXPS; i++)
        match->Open[i] = match->Close[i] = -1;
    if (RxMatch(rx)) {
        match->Open[0] = (int) (s - bop);
        match->Close[0] = (int) (rex - bop);
        return 1;
    }
    flags = fl;
    return 0;
}
