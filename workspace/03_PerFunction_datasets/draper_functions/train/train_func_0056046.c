adjustGlyphPositions(const LEUnicode chars[], le_int32 offset, le_int32 count, le_bool reverse,
                                                      LEGlyphStorage &glyphStorage, LEErrorCode &success)
{
    if (LE_FAILURE(success)) {
        return;
    }

    if (chars == NULL || offset < 0 || count < 0) {
        success = LE_ILLEGAL_ARGUMENT_ERROR;
        return;
    }

    GDEFMarkFilter filter(fGDEFTable);

    adjustMarkGlyphs(&chars[offset], count, reverse, glyphStorage, &filter, success);
}
