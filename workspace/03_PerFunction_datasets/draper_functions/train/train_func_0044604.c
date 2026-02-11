vbrpsy_compute_MS_thresholds(FLOAT eb[4][CBANDS], FLOAT thr[4][CBANDS], FLOAT cb_mld[CBANDS],
                             FLOAT ath_cb[CBANDS], FLOAT athadjust, FLOAT msfix, int n)
{
    FLOAT const msfix2 = msfix * 2;
    FLOAT const athlower = msfix > 0 ? pow(10, athadjust) : 1;
    FLOAT   rside, rmid;
    int     b;
    for (b = 0; b < n; ++b) {
        FLOAT const ebM = eb[2][b];
        FLOAT const ebS = eb[3][b];
        FLOAT const thmL = thr[0][b];
        FLOAT const thmR = thr[1][b];
        FLOAT   thmM = thr[2][b];
        FLOAT   thmS = thr[3][b];


        if (thmL <= 1.58 * thmR && thmR <= 1.58 * thmL) {
            FLOAT const mld_m = cb_mld[b] * ebS;
            FLOAT const mld_s = cb_mld[b] * ebM;
            rmid = Max(thmM, Min(thmS, mld_m));
            rside = Max(thmS, Min(thmM, mld_s));
        }
        else {
            rmid = thmM;
            rside = thmS;
        }
        if (msfix > 0) {


            FLOAT   thmLR, thmMS;
            FLOAT const ath = ath_cb[b] * athlower;
            thmLR = Min(Max(thmL, ath), Max(thmR, ath));
            thmM = Max(rmid, ath);
            thmS = Max(rside, ath);
            thmMS = thmM + thmS;
            if (thmMS > 0 && (thmLR * msfix2) < thmMS) {
                FLOAT const f = thmLR * msfix2 / thmMS;
                thmM *= f;
                thmS *= f;
                assert(thmMS > 0);
            }
            rmid = Min(thmM, rmid);
            rside = Min(thmS, rside);
        }
        if (rmid > ebM) {
            rmid = ebM;
        }
        if (rside > ebS) {
            rside = ebS;
        }
        thr[2][b] = rmid;
        thr[3][b] = rside;
    }
}
