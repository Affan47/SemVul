add(const UnicodeString& basePattern,
                const PtnSkeleton& skeleton,
                const UnicodeString& value,
                UBool skeletonWasSpecified,
                UErrorCode &status) {
    UChar baseChar = basePattern.charAt(0);
    PtnElem *curElem, *baseElem;
    status = U_ZERO_ERROR;


    if ((baseChar >= CAP_A) && (baseChar <= CAP_Z)) {
        baseElem = boot[baseChar-CAP_A];
    }
    else {
        if ((baseChar >=LOW_A) && (baseChar <= LOW_Z)) {
            baseElem = boot[26+baseChar-LOW_A];
         }
         else {
             status = U_ILLEGAL_CHARACTER;
             return;
         }
    }

    if (baseElem == NULL) {
        if ((curElem = new PtnElem(basePattern, value)) == NULL ) {

            status = U_MEMORY_ALLOCATION_ERROR;
            return;
        }
        if (baseChar >= LOW_A) {
            boot[26 + (baseChar-LOW_A)] = curElem;
        }
        else {
            boot[baseChar-CAP_A] = curElem;
        }
        curElem->skeleton = new PtnSkeleton(skeleton);
        curElem->skeletonWasSpecified = skeletonWasSpecified;
    }
    if ( baseElem != NULL ) {
        curElem = getDuplicateElem(basePattern, skeleton, baseElem);

        if (curElem == NULL) {

            curElem = baseElem;
            while( curElem -> next != NULL )
            {
                curElem = curElem->next;
            }
            if ((curElem->next = new PtnElem(basePattern, value)) == NULL ) {

                status = U_MEMORY_ALLOCATION_ERROR;
                return;
            }
            curElem=curElem->next;
            curElem->skeleton = new PtnSkeleton(skeleton);
            curElem->skeletonWasSpecified = skeletonWasSpecified;
        }
        else {

            if ( !isDupAllowed ) {
                return;
            }

            curElem->pattern = value;
        }
    }
}
