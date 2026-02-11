makeFCDAndAppend(const UChar *src, const UChar *limit,
                                       UBool doMakeFCD,
                                       UnicodeString &safeMiddle,
                                       ReorderingBuffer &buffer,
                                       UErrorCode &errorCode) const {
    if(!buffer.isEmpty()) {
        const UChar *firstBoundaryInSrc=findNextFCDBoundary(src, limit);
        if(src!=firstBoundaryInSrc) {
            const UChar *lastBoundaryInDest=findPreviousFCDBoundary(buffer.getStart(),
                                                                    buffer.getLimit());
            int32_t destSuffixLength=(int32_t)(buffer.getLimit()-lastBoundaryInDest);
            UnicodeString middle(lastBoundaryInDest, destSuffixLength);
            buffer.removeSuffix(destSuffixLength);
            safeMiddle=middle;
            middle.append(src, (int32_t)(firstBoundaryInSrc-src));
            const UChar *middleStart=middle.getBuffer();
            makeFCD(middleStart, middleStart+middle.length(), &buffer, errorCode);
            if(U_FAILURE(errorCode)) {
                return;
            }
            src=firstBoundaryInSrc;
        }
    }
    if(doMakeFCD) {
        makeFCD(src, limit, &buffer, errorCode);
    } else {
        if(limit==NULL) {
            limit=u_strchr(src, 0);
        }
        buffer.appendZeroCC(src, limit, errorCode);
    }
}
