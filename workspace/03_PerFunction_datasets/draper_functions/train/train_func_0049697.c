sameCEs(const int64_t ces1[], int32_t ces1Length,
                          const int64_t ces2[], int32_t ces2Length) {
    if(ces1Length != ces2Length) {
        return FALSE;
    }
    U_ASSERT(ces1Length <= Collation::MAX_EXPANSION_LENGTH);
    for(int32_t i = 0; i < ces1Length; ++i) {
        if(ces1[i] != ces2[i]) { return FALSE; }
    }
    return TRUE;
}
