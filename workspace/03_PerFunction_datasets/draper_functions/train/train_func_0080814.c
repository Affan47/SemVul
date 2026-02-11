calcStringSetLength(uint32_t set[8], const char *s) {
    int32_t length=0;
    char c;

    while((c=*s++)!=0) {
        SET_ADD(set, c);
        ++length;
    }
    return length;
}
