Fold(unsigned int startPos, int length, int initStyle, IDocument *pAccess) {

    LexAccessor styler(pAccess);

    unsigned int endPos = startPos + length;
    int visibleChars = 0;
    int currentLine = styler.GetLine(startPos);
    int levelCurrent = SC_FOLDLEVELBASE;
    if (currentLine > 0)
        levelCurrent = styler.LevelAt(currentLine-1) >> 16;
    int levelMinCurrent = levelCurrent;
    int levelNext = levelCurrent;
    char chNext = styler[startPos];
    int styleNext = styler.StyleAt(startPos);
    int style = initStyle;
    for (unsigned int i = startPos; i < endPos; i++) {
        char ch = chNext;
        chNext = styler.SafeGetCharAt(i + 1);
        style = styleNext;
        styleNext = styler.StyleAt(i + 1);
        bool atEOL = (ch == '\r' && chNext != '\n') || (ch == '\n');
        if (style == SCE_VISUALPROLOG_OPERATOR) {
            if (ch == '{') {


                if (levelMinCurrent > levelNext) {
                    levelMinCurrent = levelNext;
                }
                levelNext++;
            } else if (ch == '}') {
                levelNext--;
            }
        }
        if (!IsASpace(ch))
            visibleChars++;
        if (atEOL || (i == endPos-1)) {
            int levelUse = levelCurrent;
            int lev = levelUse | levelNext << 16;
            if (levelUse < levelNext)
                lev |= SC_FOLDLEVELHEADERFLAG;
            if (lev != styler.LevelAt(currentLine)) {
                styler.SetLevel(currentLine, lev);
            }
            currentLine++;
            levelCurrent = levelNext;
            levelMinCurrent = levelCurrent;
            if (atEOL && (i == static_cast<unsigned int>(styler.Length()-1))) {

                styler.SetLevel(currentLine, (levelCurrent | levelCurrent << 16) | SC_FOLDLEVELWHITEFLAG);
            }
            visibleChars = 0;
        }
    }
}
