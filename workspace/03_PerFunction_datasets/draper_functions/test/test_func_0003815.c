process(const LookupProcessor *lookupProcessor,
                                                         GlyphIterator *glyphIterator,
                                                         const LEFontInstance *fontInstance,
                                                         LEErrorCode& success)const
{
    if (LE_FAILURE(success)) {
        return 0;
    }

    le_uint16 gCount = SWAPW(glyphCount);
    le_uint16 subCount = SWAPW(substCount);
    le_int32 position = glyphIterator->getCurrStreamPosition();


    glyphIterator->prev();

    if (ContextualSubstitutionBase::matchGlyphCoverages(coverageTableOffsetArray, gCount, glyphIterator, (const char *) this)) {
        const SubstitutionLookupRecord *substLookupRecordArray =
            (const SubstitutionLookupRecord *) &coverageTableOffsetArray[gCount];

        ContextualSubstitutionBase::applySubstitutionLookups(lookupProcessor, substLookupRecordArray, subCount, glyphIterator, fontInstance, position, success);

        return gCount + 1;
    }

    glyphIterator->setCurrStreamPosition(position);

    return 0;
}
