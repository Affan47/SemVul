glyphProcessing(const LEUnicode chars[], le_int32 offset, le_int32 count, le_int32 max, le_bool rightToLeft,
                    LEGlyphStorage &glyphStorage, LEErrorCode &success)
{
    if (LE_FAILURE(success)) {
        return 0;
    }

    if (chars == NULL || offset < 0 || count < 0 || max < 0 || offset >= max || offset + count > max) {
        success = LE_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }

    le_int32 retCount = OpenTypeLayoutEngine::glyphProcessing(chars, offset, count, max, rightToLeft, glyphStorage, success);

    if (LE_FAILURE(success)) {
        return 0;
    }

    if (fVersion2) {
        IndicReordering::finalReordering(glyphStorage,retCount);
        IndicReordering::applyPresentationForms(glyphStorage,retCount);
        OpenTypeLayoutEngine::glyphSubstitution(count,max, rightToLeft, glyphStorage, success);
    } else {
        IndicReordering::adjustMPres(fMPreFixups, glyphStorage, success);
    }
    return retCount;
}
