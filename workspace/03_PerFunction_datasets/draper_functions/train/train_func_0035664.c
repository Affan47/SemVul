LineIndented(int Row, const char *indentchars) {
    ELine *l;

    if (Row < 0) return 0;
    if (Row >= RCount) return 0;
    l = RLine(Row);
    return ScreenPos(l, LineIndentedCharCount(l, indentchars));
}
