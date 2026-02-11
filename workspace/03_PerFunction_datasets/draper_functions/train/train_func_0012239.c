array_write16(struct SRBRoot *bundle, struct SResource *res,
              UErrorCode *status) {
    struct SResource *current;
    int32_t res16 = 0;

    if (U_FAILURE(*status)) {
        return;
    }
    if (res->u.fArray.fCount == 0 && gFormatVersion > 1) {
        res->fRes = URES_MAKE_EMPTY_RESOURCE(URES_ARRAY);
        res->fWritten = TRUE;
        return;
    }
    for (current = res->u.fArray.fFirst; current != NULL; current = current->fNext) {
        res_write16(bundle, current, status);
        res16 |= makeRes16(current->fRes);
    }
    if (U_SUCCESS(*status) && res->u.fArray.fCount <= 0xffff && res16 >= 0 && gFormatVersion > 1) {
        uint16_t *p16 = reserve16BitUnits(bundle, 1 + res->u.fArray.fCount, status);
        if (U_SUCCESS(*status)) {
            res->fRes = URES_MAKE_RESOURCE(URES_ARRAY16, bundle->f16BitUnitsLength);
            *p16++ = (uint16_t)res->u.fArray.fCount;
            for (current = res->u.fArray.fFirst; current != NULL; current = current->fNext) {
                *p16++ = (uint16_t)makeRes16(current->fRes);
            }
            bundle->f16BitUnitsLength += 1 + res->u.fArray.fCount;
            res->fWritten = TRUE;
        }
    }
}
