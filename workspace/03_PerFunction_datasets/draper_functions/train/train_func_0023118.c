zzlDeleteRangeByScore(unsigned char *zl, zrangespec *range, unsigned long *deleted) {
    unsigned char *eptr, *sptr;
    double score;
    unsigned long num = 0;

    if (deleted != NULL) *deleted = 0;

    eptr = zzlFirstInRange(zl,range);
    if (eptr == NULL) return zl;


    while ((sptr = ziplistNext(zl,eptr)) != NULL) {
        score = zzlGetScore(sptr);
        if (zslValueLteMax(score,range)) {

            zl = ziplistDelete(zl,&eptr);
            zl = ziplistDelete(zl,&eptr);
            num++;
        } else {

            break;
        }
    }

    if (deleted != NULL) *deleted = num;
    return zl;
}
