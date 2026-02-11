terminatePSKLevel(int32_t level, int32_t maxLevel, int32_t &i, uint8_t *dest) {
    if(level < maxLevel) {
        dest[i++] = UCOL_LEVELTERMINATOR;
    } else {
        dest[i++] = 0;
    }
}
