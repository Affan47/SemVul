adjustFieldTypes(const UnicodeString& pattern,
                                           const PtnSkeleton* specifiedSkeleton,
                                           int32_t flags,
                                           UDateTimePatternMatchOptions options) {
    UnicodeString newPattern;
    fp->set(pattern);
    for (int32_t i=0; i < fp->itemNumber; i++) {
        UnicodeString field = fp->items[i];
        if ( fp->isQuoteLiteral(field) ) {

            UnicodeString quoteLiteral;
            fp->getQuoteLiteral(quoteLiteral, &i);
            newPattern += quoteLiteral;
        }
        else {
            if (fp->isPatternSeparator(field)) {
                newPattern+=field;
                continue;
            }
            int32_t canonicalIndex = fp->getCanonicalIndex(field);
            if (canonicalIndex < 0) {
                newPattern+=field;
                continue;
            }
            const dtTypeElem *row = &dtTypes[canonicalIndex];
            int32_t typeValue = row->field;
            if ((flags & kDTPGFixFractionalSeconds) != 0 && typeValue == UDATPG_SECOND_FIELD) {
                UnicodeString newField=dtMatcher->skeleton.original[UDATPG_FRACTIONAL_SECOND_FIELD];
                field = field + decimal + newField;
            } else if (dtMatcher->skeleton.type[typeValue]!=0) {


                    UnicodeString reqField = dtMatcher->skeleton.original[typeValue];
                    int32_t reqFieldLen = reqField.length();
                    if (reqField.charAt(0) == CAP_E && reqFieldLen < 3)
                        reqFieldLen = 3;
                    int32_t adjFieldLen = reqFieldLen;
                    if ( (typeValue==UDATPG_HOUR_FIELD && (options & UDATPG_MATCH_HOUR_FIELD_LENGTH)==0) ||
                         (typeValue==UDATPG_MINUTE_FIELD && (options & UDATPG_MATCH_MINUTE_FIELD_LENGTH)==0) ||
                         (typeValue==UDATPG_SECOND_FIELD && (options & UDATPG_MATCH_SECOND_FIELD_LENGTH)==0) ) {
                         adjFieldLen = field.length();
                    } else if (specifiedSkeleton) {
                        UnicodeString skelField = specifiedSkeleton->original[typeValue];
                        int32_t skelFieldLen = skelField.length();
                        UBool patFieldIsNumeric = (row->type > 0);
                        UBool skelFieldIsNumeric = (specifiedSkeleton->type[typeValue] > 0);
                        if (skelFieldLen == reqFieldLen || (patFieldIsNumeric && !skelFieldIsNumeric) || (skelFieldIsNumeric && !patFieldIsNumeric)) {

                            adjFieldLen = field.length();
                        }
                    }
                    UChar c = (typeValue!= UDATPG_HOUR_FIELD && typeValue!= UDATPG_MONTH_FIELD &&
                               typeValue!= UDATPG_WEEKDAY_FIELD && (typeValue!= UDATPG_YEAR_FIELD || reqField.charAt(0)==CAP_Y))?
                        reqField.charAt(0): field.charAt(0);
                    if (typeValue == UDATPG_HOUR_FIELD && (flags & kDTPGSkeletonUsesCapJ) != 0) {
                        c = fDefaultHourFormatChar;
                    }
                    field.remove();
                    for (int32_t i=adjFieldLen; i>0; --i) {
                        field+=c;
                    }
            }
            newPattern+=field;
        }
    }
    return newPattern;
}
