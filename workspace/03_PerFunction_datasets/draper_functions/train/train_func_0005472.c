ucol_tok_doSetTop(UColTokenParser *src, UErrorCode *status) {


    UChar buff[5];
    src->parsedToken.charsOffset = (uint32_t)(src->extraCurrent - src->source);
    buff[0] = 0xFFFE;
    buff[1] = (UChar)(ucolIndirectBoundaries[src->parsedToken.indirectIndex].startCE >> 16);
    buff[2] = (UChar)(ucolIndirectBoundaries[src->parsedToken.indirectIndex].startCE & 0xFFFF);
    if(ucolIndirectBoundaries[src->parsedToken.indirectIndex].startContCE == 0) {
        src->parsedToken.charsLen = 3;
        ucol_tok_addToExtraCurrent(src, buff, 3, status);
    } else {
        buff[3] = (UChar)(ucolIndirectBoundaries[src->parsedToken.indirectIndex].startContCE >> 16);
        buff[4] = (UChar)(ucolIndirectBoundaries[src->parsedToken.indirectIndex].startContCE & 0xFFFF);
        src->parsedToken.charsLen = 5;
        ucol_tok_addToExtraCurrent(src, buff, 5, status);
    }
    return TRUE;
}
