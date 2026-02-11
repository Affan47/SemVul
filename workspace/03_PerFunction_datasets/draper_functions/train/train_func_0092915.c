SelfInsert(ExState &) {
    if (LastEventChar != -1)
        return TypeChar(char(LastEventChar));
    return 0;
}
