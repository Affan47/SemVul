previousHasTccc() const {
    U_ASSERT(state == CHECK_BWD && pos != 0);
    UChar32 c = u8[pos - 1];
    if(c < 0x80) { return FALSE; }
    int32_t i = pos;
    U8_PREV_OR_FFFD(u8, 0, i, c);
    if(c > 0xffff) { c = U16_LEAD(c); }
    return CollationFCD::hasTccc(c);
}
