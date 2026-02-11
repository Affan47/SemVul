CheckLabel(EBuffer *B, int Line) {
    PELine L = B->RLine(Line);
    int P = B->CharOffset(L, B->LineIndented(Line));
    int Cnt = 0;

    PRINTF(("CHECKING LABEL\n"));
    if (Line > 0 && B->RLine(Line - 1)->StateE != hsC_Normal)
        return 0;

    while ((P < L->Count) &&
           (L->Chars[P] == ' ' || L->Chars[P] == 9)) P++;

    while (P < L->Count) {
        if (Cnt > 0)
            if (L->Chars[P] == ':' && (Cnt == 1 || L->Chars[P + 1] != ':')) {
                PRINTF(("CHECKING LABEL -> 1!\n"));
                return 1;
            }
        if (!ISNAME(L->Chars[P])) {
            PRINTF(("NONCHECKING LABEL -> 0\n"));
            return 0;
        }
        Cnt++;
        P++;
    }
    PRINTF(("CHECKING LABEL -> 0\n"));
    return 0;
}
