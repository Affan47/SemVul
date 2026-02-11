RxExecMatch(RxNode *Regexp, const char *Data, size_t Len, const char *Start, RxMatchRes *Match, unsigned int RxOpt) {
    if (Regexp == 0) return 0;

    match = Match;
    bop = Data;
    eop = Data + Len;

    flags = RxOpt;

    return RxTry(Regexp, Start);
}
