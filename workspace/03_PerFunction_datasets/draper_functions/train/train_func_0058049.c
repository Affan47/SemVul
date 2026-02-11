IsValidHrule(const unsigned int endPos, StyleContext &sc) {
    int c, count = 1;
    unsigned int i = 0;
    while (++i) {
        c = sc.GetRelative(i);
        if (c == sc.ch)
            ++count;

        else if (!IsASpaceOrTab(c) || sc.currentPos + i == endPos) {

            if ((IsNewline(c) || sc.currentPos + i == endPos) &&
                    count >= 3 && !HasPrevLineContent(sc)) {
                sc.SetState(SCE_MARKDOWN_HRULE);
                sc.Forward(i);
                sc.SetState(SCE_MARKDOWN_LINE_BEGIN);
                return true;
            }
            else {
                sc.SetState(SCE_MARKDOWN_DEFAULT);
		return false;
            }
        }
    }
    return false;
}
