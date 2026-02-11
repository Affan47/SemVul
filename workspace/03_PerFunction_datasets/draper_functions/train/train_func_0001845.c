process(LEGlyphStorage &glyphStorage, GlyphPositionAdjustments *glyphPositionAdjustments, le_bool rightToLeft,
                                          LETag scriptTag, LETag languageTag,
                                          const GlyphDefinitionTableHeader *glyphDefinitionTableHeader, LEErrorCode &success,
                                          const LEFontInstance *fontInstance, const FeatureMap *featureMap, le_int32 featureMapCount, le_bool featureOrder) const
{
    if (LE_FAILURE(success)) {
        return;
    }

    GlyphPositioningLookupProcessor processor(this, scriptTag, languageTag, featureMap, featureMapCount, featureOrder, success);
    if (LE_FAILURE(success)) {
        return;
    }

    processor.process(glyphStorage, glyphPositionAdjustments, rightToLeft, glyphDefinitionTableHeader, fontInstance, success);

    glyphPositionAdjustments->applyCursiveAdjustments(glyphStorage, rightToLeft, fontInstance);
}
