ucol_setReorderCodesFromParser(UCollator *coll, UColTokenParser *parser, UErrorCode *status) {
    if (U_FAILURE(*status)) {
        return;
    }

    if (parser->reorderCodesLength == 0 || parser->reorderCodes == NULL) {
        return;
    }

    coll->reorderCodesLength = 0;
    if (coll->reorderCodes != NULL && coll->freeReorderCodesOnClose == TRUE) {
        uprv_free(coll->reorderCodes);
    }
    coll->reorderCodes = NULL;
    coll->freeReorderCodesOnClose = FALSE;

    if (coll->defaultReorderCodes != NULL && coll->freeDefaultReorderCodesOnClose == TRUE) {
        uprv_free(coll->defaultReorderCodes);
    }
    coll->freeDefaultReorderCodesOnClose = FALSE;
    coll->defaultReorderCodesLength = parser->reorderCodesLength;
    coll->defaultReorderCodes =  (int32_t*) uprv_malloc(coll->defaultReorderCodesLength * sizeof(int32_t));
    if (coll->defaultReorderCodes == NULL) {
        *status = U_MEMORY_ALLOCATION_ERROR;
        return;
    }
    uprv_memcpy(coll->defaultReorderCodes, parser->reorderCodes, coll->defaultReorderCodesLength * sizeof(int32_t));
    coll->freeDefaultReorderCodesOnClose = TRUE;

    coll->reorderCodesLength = parser->reorderCodesLength;
    coll->reorderCodes = (int32_t*) uprv_malloc(coll->reorderCodesLength * sizeof(int32_t));
    if (coll->reorderCodes == NULL) {
        *status = U_MEMORY_ALLOCATION_ERROR;
        return;
    }
    uprv_memcpy(coll->reorderCodes, parser->reorderCodes, coll->reorderCodesLength * sizeof(int32_t));
    coll->freeReorderCodesOnClose = TRUE;
}
