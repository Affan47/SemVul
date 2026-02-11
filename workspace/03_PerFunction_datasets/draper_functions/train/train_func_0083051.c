unorm_iterate(UCharIterator *src, UBool forward,
              UChar *dest, int32_t destCapacity,
              UNormalizationMode mode, int32_t options,
              UBool doNormalize, UBool *pNeededToNormalize,
              UErrorCode *pErrorCode) {
    const Normalizer2 *n2=Normalizer2Factory::getInstance(mode, *pErrorCode);
    const UnicodeSet *uni32;
    if(options&UNORM_UNICODE_3_2) {
        uni32=uniset_getUnicode32Instance(*pErrorCode);
    } else {
        uni32=NULL;
    }

    if(U_FAILURE(*pErrorCode)) {
        return 0;
    }

    FilteredNormalizer2 fn2(*n2, *uni32);
    if(options&UNORM_UNICODE_3_2) {
        n2=&fn2;
    }

    if( destCapacity<0 || (dest==NULL && destCapacity>0) ||
        src==NULL
    ) {
        *pErrorCode=U_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }

    if(pNeededToNormalize!=NULL) {
        *pNeededToNormalize=FALSE;
    }
    if(!(forward ? src->hasNext(src) : src->hasPrevious(src))) {
        return u_terminateUChars(dest, destCapacity, 0, pErrorCode);
    }

    UnicodeString buffer;
    UChar32 c;
    if(forward) {

        buffer.append(uiter_next32(src));

        while((c=uiter_next32(src))>=0) {
            if(n2->hasBoundaryBefore(c)) {

                src->move(src, -U16_LENGTH(c), UITER_CURRENT);
                break;
            } else {
                buffer.append(c);
            }
        }
    } else {
        while((c=uiter_previous32(src))>=0) {

            buffer.insert(0, c);

            if(n2->hasBoundaryBefore(c)) {
                break;
            }
        }
    }

    UnicodeString destString(dest, 0, destCapacity);
    if(buffer.length()>0 && doNormalize) {
        n2->normalize(buffer, destString, *pErrorCode).extract(dest, destCapacity, *pErrorCode);
        if(pNeededToNormalize!=NULL && U_SUCCESS(*pErrorCode)) {
            *pNeededToNormalize= destString!=buffer;
        }
        return destString.length();
    } else {

        return buffer.extract(dest, destCapacity, *pErrorCode);
    }
}
