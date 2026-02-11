glyphPostProcessing(LEGlyphStorage &tempGlyphStorage, LEGlyphStorage &glyphStorage, LEErrorCode &success)
{
    if (LE_FAILURE(success)) {
        return 0;
    }

    glyphStorage.adoptGlyphArray(tempGlyphStorage);
    glyphStorage.adoptCharIndicesArray(tempGlyphStorage);
    glyphStorage.adoptAuxDataArray(tempGlyphStorage);
    glyphStorage.adoptGlyphCount(tempGlyphStorage);

    return glyphStorage.getGlyphCount();
}
