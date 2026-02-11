characterProcessing(const LEUnicode chars[], le_int32 offset, le_int32 count, le_int32 max, le_bool rightToLeft,
        LEUnicode *&outChars, LEGlyphStorage &glyphStorage, LEErrorCode &success)
{
    if (LE_FAILURE(success)) {
        return 0;
    }

    if (chars == NULL || offset < 0 || count < 0 || max < 0 || offset >= max || offset + count > max) {
        success = LE_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }

    le_int32 worstCase = count * IndicReordering::getWorstCaseExpansion(fScriptCode);

    outChars = LE_NEW_ARRAY(LEUnicode, worstCase);

    if (outChars == NULL) {
        success = LE_MEMORY_ALLOCATION_ERROR;
        return 0;
    }

    glyphStorage.allocateGlyphArray(worstCase, rightToLeft, success);
    glyphStorage.allocateAuxData(success);

    if (LE_FAILURE(success)) {
        LE_DELETE_ARRAY(outChars);
        return 0;
    }


    le_int32 outCharCount;
    if (fVersion2) {
        outCharCount = IndicReordering::v2process(&chars[offset], count, fScriptCode, outChars, glyphStorage);
    } else {
        outCharCount = IndicReordering::reorder(&chars[offset], count, fScriptCode, outChars, glyphStorage, &fMPreFixups, success);
    }

    if (LE_FAILURE(success)) {
        LE_DELETE_ARRAY(outChars);
        return 0;
    }

    glyphStorage.adoptGlyphCount(outCharCount);
    return outCharCount;
}
