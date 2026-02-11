permute(UnicodeString &source, UBool skipZeros, Hashtable *result, UErrorCode &status) {
    if(U_FAILURE(status)) {
        return;
    }

    int32_t i = 0;


    if (source.length() <= 2 && source.countChar32() <= 1) {
        UnicodeString *toPut = new UnicodeString(source);

        if (toPut == 0) {
            status = U_MEMORY_ALLOCATION_ERROR;
            return;
        }
        result->put(source, toPut, status);
        return;
    }


    UChar32 cp;
    Hashtable subpermute(status);
    if(U_FAILURE(status)) {
        return;
    }
    subpermute.setValueDeleter(uprv_deleteUObject);

    for (i = 0; i < source.length(); i += U16_LENGTH(cp)) {
        cp = source.char32At(i);
        const UHashElement *ne = NULL;
        int32_t el = -1;
        UnicodeString subPermuteString = source;


        if (skipZeros && i != 0 && u_getCombiningClass(cp) == 0) {

            continue;
        }

        subpermute.removeAll();


        permute(subPermuteString.replace(i, U16_LENGTH(cp), NULL, 0), skipZeros, &subpermute, status);

        if(U_FAILURE(status)) {
            return;
        }


        ne = subpermute.nextElement(el);
        while (ne != NULL) {
            UnicodeString *permRes = (UnicodeString *)(ne->value.pointer);
            UnicodeString *chStr = new UnicodeString(cp);

            if (chStr == NULL) {
                status = U_MEMORY_ALLOCATION_ERROR;
                return;
            }
            chStr->append(*permRes);

            result->put(*chStr, chStr, status);
            ne = subpermute.nextElement(el);
        }
    }

}
