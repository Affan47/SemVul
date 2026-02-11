charAt(int32_t index) const {
    if (index >= 0) {


        int32_t len2 = len & ~1;
        for (int32_t i=0; i < len2;) {
            UChar32 start = list[i++];
            int32_t count = list[i++] - start;
            if (index < count) {
                return (UChar32)(start + index);
            }
            index -= count;
        }
    }
    return (UChar32)-1;
}
