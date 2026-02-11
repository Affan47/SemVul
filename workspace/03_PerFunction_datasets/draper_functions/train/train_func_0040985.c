adjustFieldTypes(const UnicodeString& pattern,
                                           const PtnSkeleton* specifiedSkeleton,
                                           UBool fixFractionalSeconds) {
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
            if (fixFractionalSeconds && typeValue == UDATPG_SECOND_FIELD) {
                UnicodeString newField=dtMatcher->skeleton.original[UDATPG_FRACTIONAL_SECOND_FIELD];
                field = field + decimal + newField;
            }
            else {
                if (dtMatcher->skeleton.type[typeValue]!=0) {


                    UnicodeString reqField = dtMatcher->skeleton.original[typeValue];
                    int32_t reqFieldLen = reqField.length();
                    int32_t adjFieldLen = reqFieldLen;
                    if (specifiedSkeleton) {
                        UnicodeString skelField = specifiedSkeleton->original[typeValue];
                        int32_t skelFieldLen = skelField.length();
                        UBool patFieldIsNumeric = (row->type > 0);
                        UBool skelFieldIsNumeric = (specifiedSkeleton->type[typeValue] > 0);
                        if (skelFieldLen == reqFieldLen || (patFieldIsNumeric && !skelFieldIsNumeric) || (skelFieldIsNumeric && !patFieldIsNumeric)) {

                            adjFieldLen = field.length();
                        }
                    }
                    UChar c = (typeValue!= UDATPG_HOUR_FIELD)? reqField.charAt(0): field.charAt(0);
                    field.remove();
                    for (int32_t i=adjFieldLen; i>0; --i) {
                        field+=c;
                    }
                }
                newPattern+=field;
            }
        }
    }
    return newPattern;
}
