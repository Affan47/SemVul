initGMTOffsetPatterns(UErrorCode& status) {
    for (int32_t type = 0; type < UTZFMT_PAT_COUNT; type++) {
        switch (type) {
        case UTZFMT_PAT_POSITIVE_H:
        case UTZFMT_PAT_NEGATIVE_H:
            fGMTOffsetPatternItems[type] = parseOffsetPattern(fGMTOffsetPatterns[type], FIELDS_H, status);
            break;
        case UTZFMT_PAT_POSITIVE_HM:
        case UTZFMT_PAT_NEGATIVE_HM:
            fGMTOffsetPatternItems[type] = parseOffsetPattern(fGMTOffsetPatterns[type], FIELDS_HM, status);
            break;
        case UTZFMT_PAT_POSITIVE_HMS:
        case UTZFMT_PAT_NEGATIVE_HMS:
            fGMTOffsetPatternItems[type] = parseOffsetPattern(fGMTOffsetPatterns[type], FIELDS_HMS, status);
            break;
        }
    }
    checkAbuttingHoursAndMinutes();
}
