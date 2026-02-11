compareDates(const void * , const void *left, const void *right) {
    UDate l = *((UDate*)left);
    UDate r = *((UDate*)right);
    int32_t res = l < r ? -1 : (l == r ? 0 : 1);
    return res;
}
