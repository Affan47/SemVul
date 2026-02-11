previousNormalize() {
    clearBuffer();
    nextIndex=currentIndex;
    text->setIndex(currentIndex);
    if(!text->hasPrevious()) {
        return FALSE;
    }
    UnicodeString segment;
    while(text->hasPrevious()) {
        UChar32 c=text->previous32();
        segment.insert(0, c);
        if(fNorm2->hasBoundaryBefore(c)) {
            break;
        }
    }
    currentIndex=text->getIndex();
    UErrorCode errorCode=U_ZERO_ERROR;
    fNorm2->normalize(segment, buffer, errorCode);
    bufferPos=buffer.length();
    return U_SUCCESS(errorCode) && !buffer.isEmpty();
}
