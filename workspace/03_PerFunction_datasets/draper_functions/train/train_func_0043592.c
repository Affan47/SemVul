sortedAdd(UVector **vector, int32_t val) {
    int32_t i;

    if (*vector == NULL) {
        *vector = new UVector(*fStatus);
    }
    if (*vector == NULL || U_FAILURE(*fStatus)) {
        return;
    }
    UVector *vec = *vector;
    int32_t  vSize = vec->size();
    for (i=0; i<vSize; i++) {
        int32_t valAtI = vec->elementAti(i);
        if (valAtI == val) {

            return;
        }
        if (valAtI > val) {
            break;
        }
    }
    vec->insertElementAt(val, i, *fStatus);
}
