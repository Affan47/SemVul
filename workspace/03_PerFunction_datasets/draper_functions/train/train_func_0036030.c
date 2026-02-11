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

    if (!fGPOSTable.isEmpty()) {
        OpenTypeLayoutEngine::adjustGlyphPositions(chars, offset, count, reverse, glyphStorage, success);
    } else if (!fGDEFTable.isEmpty()) {
        GDEFMarkFilter filter(fGDEFTable, success);
        adjustMarkGlyphs(glyphStorage, &filter, success);
    } else {
        LEReferenceTo<GlyphDefinitionTableHeader> gdefTable(CanonShaping::glyphDefinitionTable, CanonShaping::glyphDefinitionTableLen);
        GDEFMarkFilter filter(gdefTable, success);

        adjustMarkGlyphs(&chars[offset], count, reverse, glyphStorage, &filter, success);
    }
}
