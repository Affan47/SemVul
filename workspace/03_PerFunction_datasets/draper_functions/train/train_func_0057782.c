ScreenPos(ELine *L, int Offset) {
    int ExpandTabs = BFI(this, BFI_ExpandTabs);
    int TabSize = BFI(this, BFI_TabSize);

    if (!ExpandTabs)
        return Offset;

    char *p = L->Chars;
    int Len = L->Count;
    int Pos = 0;
    int Ofs = Offset;

    if (Ofs > Len) {
        while (Len > 0) {
            if (*p++ != '\t')
                Pos++;
            else
                Pos = NextTab(Pos, TabSize);
            Len--;
        }
        Pos += Ofs - L->Count;
    } else
        while (Ofs > 0) {
            if (*p++ != '\t')
                Pos++;
            else
                Pos = NextTab(Pos, TabSize);
            Ofs--;
        }

    return Pos;
}
