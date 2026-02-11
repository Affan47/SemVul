findCodePoint(UChar32 c, int32_t lo, int32_t hi) const {


    if (c < list[lo])
        return lo;


    if (lo >= hi || c >= list[hi-1])
        return hi;


    for (;;) {
        int32_t i = (lo + hi) >> 1;
        if (i == lo) {
            break;
        } else if (c < list[i]) {
            hi = i;
        } else {
            lo = i;
        }
    }
    return hi;
}
