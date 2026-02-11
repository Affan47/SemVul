hashCode() const {
    int32_t h = options << 8;
    if((options & ALTERNATE_MASK) != 0) { h ^= variableTop; }
    h ^= reorderCodesLength;
    for(int32_t i = 0; i < reorderCodesLength; ++i) {
        h ^= (reorderCodes[i] << i);
    }
    return h;
}
