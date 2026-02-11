next32() {
    if (pos < end) {
        U16_FWD_1(text, pos, end);
        if(pos < end) {
            int32_t i = pos;
            UChar32 c;
            U16_NEXT(text, i, end, c);
            return c;
        }
    }

    pos = end;
    return DONE;
}
