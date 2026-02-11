table_preWrite(uint32_t *byteOffset,
               struct SRBRoot *bundle, struct SResource *res,
               UErrorCode *status) {
    struct SResource *current;

    if (U_FAILURE(*status)) {
        return;
    }
    for (current = res->u.fTable.fFirst; current != NULL; current = current->fNext) {
        res_preWrite(byteOffset, bundle, current, status);
    }
    if (res->u.fTable.fType == URES_TABLE) {

        res->fRes = URES_MAKE_RESOURCE(URES_TABLE, *byteOffset >> 2);
        *byteOffset += 2 + res->u.fTable.fCount * 6;
    } else {

        res->fRes = URES_MAKE_RESOURCE(URES_TABLE32, *byteOffset >> 2);
        *byteOffset += 4 + res->u.fTable.fCount * 8;
    }
}
