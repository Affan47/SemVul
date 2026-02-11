add(UChar32 start, UChar32 end) {
    if (pinCodePoint(start) < pinCodePoint(end)) {
        UChar32 range[3] = { start, end+1, UNICODESET_HIGH };
        add(range, 2, 0);
    } else if (start == end) {
        add(start);
    }
    return *this;
}
