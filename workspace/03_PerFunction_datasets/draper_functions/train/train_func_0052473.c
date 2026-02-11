getSecondaryBefore(uint32_t p, uint32_t s) const {
    int32_t index;
    uint32_t previousSec, sec;
    if(p == 0) {
        index = (int32_t)elements[IX_FIRST_SECONDARY_INDEX];

        previousSec = 0;
        sec = elements[index] >> 16;
    } else {
        index = findPrimary(p) + 1;
        previousSec = Collation::MERGE_SEPARATOR_WEIGHT16;
        sec = Collation::COMMON_WEIGHT16;
    }
    U_ASSERT(s >= sec);
    while(s > sec) {
        previousSec = sec;
        U_ASSERT((elements[index] & SEC_TER_DELTA_FLAG) != 0);
        sec = elements[index++] >> 16;
    }
    U_ASSERT(sec == s);
    return previousSec;
}
