nextCharLL() {
    UChar32       ch;
    UnicodeString &pattern = fRXPat->fPattern;

    if (fPeekChar != -1) {
        ch = fPeekChar;
        fPeekChar = -1;
        return ch;
    }
    if (fPatternLength==0 || fNextIndex >= fPatternLength) {
        return (UChar32)-1;
    }
    ch         = pattern.char32At(fNextIndex);
    fNextIndex = pattern.moveIndex32(fNextIndex, 1);

    if (ch == chCR ||
        ch == chNEL ||
        ch == chLS   ||
        ch == chLF && fLastChar != chCR) {


        fLineNum++;
        fCharNum=0;
    }
    else {


        if (ch != chLF) {
            fCharNum++;
        }
    }
    fLastChar = ch;
    return ch;
}
