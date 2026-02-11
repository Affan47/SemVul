parseSpecialCasing(const char *filename, UErrorCode *pErrorCode) {
    char *fields[5][2];
    int32_t i, j;

    if(pErrorCode==NULL || U_FAILURE(*pErrorCode)) {
        return;
    }

    u_parseDelimitedFile(filename, ';', fields, 5, specialCasingLineFn, NULL, pErrorCode);


    if(specialCasingCount>0) {
        uprv_sortArray(specialCasings, specialCasingCount, sizeof(SpecialCasing),
                       compareSpecialCasings, NULL, FALSE, pErrorCode);
    }
    if(U_FAILURE(*pErrorCode)) {
        return;
    }


    j=0;
    for(i=1; i<specialCasingCount; ++i) {
        if(specialCasings[i-1].code==specialCasings[i].code) {

            specialCasings[i-1].code=0x7fffffff;
            specialCasings[i].isComplex=TRUE;
            specialCasings[i].lowerCase[0]=0;
            specialCasings[i].upperCase[0]=0;
            specialCasings[i].titleCase[0]=0;
            ++j;
        }
    }


    if(j>0) {
        uprv_sortArray(specialCasings, specialCasingCount, sizeof(SpecialCasing),
                       compareSpecialCasings, NULL, FALSE, pErrorCode);
        specialCasingCount-=j;
    }
    if(U_FAILURE(*pErrorCode)) {
        return;
    }


    uset_add(caseSensitive, 0x3c2);
}
