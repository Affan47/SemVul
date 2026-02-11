replacechar(src, ch1, ch2)
    char ch1, ch2;
    STR src; {

    pchar pch;
    if (ch1 == ch2) return;
    for (pch = src; *pch; pch++) if (*pch == ch1) *pch = ch2;
}
