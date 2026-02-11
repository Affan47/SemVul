ucol_uprv_getCaseBits(const UCollator *UCA, const UChar *src, uint32_t len, UErrorCode *status) {
    uint32_t i = 0;
    UChar n[128];
    uint32_t nLen = 0;
    uint32_t uCount = 0, lCount = 0;

    collIterate s;
    uint32_t order = 0;

    if(U_FAILURE(*status)) {
        return UCOL_LOWER_CASE;
    }

    nLen = unorm_normalize(src, len, UNORM_NFKD, 0, n, 128, status);
    if(U_SUCCESS(*status)) {
        for(i = 0; i < nLen; i++) {
            uprv_init_collIterate(UCA, &n[i], 1, &s, status);
            order = ucol_getNextCE(UCA, &s, status);
            if(isContinuation(order)) {
                *status = U_INTERNAL_PROGRAM_ERROR;
                return UCOL_LOWER_CASE;
            }
            if((order&UCOL_CASE_BIT_MASK)== UCOL_UPPER_CASE) {
                uCount++;
            } else {
                if(u_islower(n[i])) {
                    lCount++;
                } else if(U_SUCCESS(*status)) {
                    UChar sk[1], lk[1];
                    u_toSmallKana(&n[i], 1, sk, 1, status);
                    u_toLargeKana(&n[i], 1, lk, 1, status);
                    if(sk[0] == n[i] && lk[0] != n[i]) {
                        lCount++;
                    }
                }
            }
        }
    }

    if(uCount != 0 && lCount != 0) {
        return UCOL_MIXED_CASE;
    } else if(uCount != 0) {
        return UCOL_UPPER_CASE;
    } else {
        return UCOL_LOWER_CASE;
    }
}
