TrimLine(int Row) {
    PELine L = RLine(Row);
    int P, X, E;

    if (L->Count == 0) return 1;
    P = L->Count;
    while ((P > 0) && ((L->Chars[P - 1] == ' ') || (L->Chars[P - 1] == 9)))
        P--;
    X = ScreenPos(L, P);
    E = ScreenPos(L, L->Count);
    if (E - X > 0)
        if (DelText(Row, X, E - X, 1) == 0) return 0;
    return 1;
}
