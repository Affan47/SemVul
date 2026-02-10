Indent_REXX(EBuffer *B, int Line, int PosCursor) {
    int I;
    hsState *StateMap = NULL;
    int StateLen = 0;
    int OI;

    OI = I = B->LineIndented(Line);
    if (I != 0) B->IndentLine(Line, 0);
    if (B->GetMap(Line, &StateLen, &StateMap) == 0) return 0;

    if (StateLen > 0) {
        if (StateMap[0] == hsREXX_Comment) {
            I = IndentComment(B, Line, StateLen, StateMap);
        } else {
            I = IndentNormal(B, Line, StateLen, StateMap);
        }
    } else {
        I = IndentNormal(B, Line, 0, NULL);
    }
    if (StateMap)
        free(StateMap);
    if (I >= 0)
        B->IndentLine(Line, I);
    else
        I = 0;
    if (PosCursor == 1) {
        int X = B->CP.Col;

        X = X - OI + I;
        if (X < I) X = I;
        if (X < 0) X = 0;
        if (X > B->LineLen(Line)) {
            X = B->LineLen(Line);
            if (X < I) X = I;
        }
        if (B->SetPosR(X, Line) == 0) return 0;
    } else if (PosCursor == 2) {
        if (B->SetPosR(I, Line) == 0) return 0;
    }
    return 1;
}
