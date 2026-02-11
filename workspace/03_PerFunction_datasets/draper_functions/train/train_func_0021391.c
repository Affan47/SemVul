RetrieveFPos(const char *FileName, int &Row, int &Col) {
    int L = 0, R = FPHistoryCount, M;
    int cmp;

    if (FPHistory == 0)
        return 0;

    while (L < R) {
        M = (L + R) / 2;
        cmp = filecmp(FileName, FPHistory[M]->FileName);
        if (cmp == 0) {
            Row = FPHistory[M]->Row;
            Col = FPHistory[M]->Col;
            return 1;
        } else if (cmp < 0) {
            R = M;
        } else {
            L = M + 1;
        }
    }
    return 0;
}
