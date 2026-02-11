GetCharFromEvent(TEvent &E, char *Ch) {
    *Ch = 0;
    if (E.Key.Code & kfModifier)
        return 0;
    if (kbCode(E.Key.Code) == kbEsc) { *Ch = 27; return 1; }
    if (kbCode(E.Key.Code) == kbEnter) { *Ch = 13; return 1; }
    if (kbCode(E.Key.Code) == (kbEnter | kfCtrl)) { *Ch = 10; return 1; }
    if (kbCode(E.Key.Code) == kbBackSp) { *Ch = 8; return 1; }
    if (kbCode(E.Key.Code) == (kbBackSp | kfCtrl)) { *Ch = 127; return 1; }
    if (kbCode(E.Key.Code) == kbTab) { *Ch = 9; return 1; }
    if (kbCode(E.Key.Code) == kbDel) { *Ch = 127; return 1; }
    if (keyType(E.Key.Code) == kfCtrl) {
        *Ch = (char) (E.Key.Code & 0x1F);
        return 1;
    }
    if (isAscii(E.Key.Code)) {
        *Ch = (char)E.Key.Code;
        return 1;
    }
    return 0;
}
