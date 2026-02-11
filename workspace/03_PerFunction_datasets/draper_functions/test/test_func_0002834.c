checkAlias(const char *itemName,
           Resource res, const UChar *alias, int32_t length, UBool useResSuffix,
           CheckDependency check, void *context, UErrorCode *pErrorCode) {
    int32_t i;

    if(!uprv_isInvariantUString(alias, length)) {
        fprintf(stderr, "icupkg/ures_enumDependencies(%s res=%08x) alias string contains non-invariant characters\n",
                        itemName, res);
        *pErrorCode=U_INVALID_CHAR_FOUND;
        return;
    }


    for(i=0; i<length && alias[i]!=SLASH; ++i) {}

    if(res_getPublicType(res)==URES_ALIAS) {


        if(i==0) {
            return;
        }


        length=i;
    } else  {

        if(i!=length) {
            fprintf(stderr, "icupkg/ures_enumDependencies(%s res=%08x) %%ALIAS contains a '/'\n",
                            itemName, res);
            *pErrorCode=U_UNSUPPORTED_ERROR;
            return;
        }
    }


    char localeID[32];
    if(length>=(int32_t)sizeof(localeID)) {
        fprintf(stderr, "icupkg/ures_enumDependencies(%s res=%08x) alias locale ID length %ld too long\n",
                        itemName, res, (long)length);
        *pErrorCode=U_BUFFER_OVERFLOW_ERROR;
        return;
    }
    u_UCharsToChars(alias, localeID, length);
    localeID[length]=0;

    checkIDSuffix(itemName, localeID, -1, (useResSuffix ? ".res" : ""), check, context, pErrorCode);
}
