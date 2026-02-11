process(const LEReferenceTo<CursiveAttachmentSubtable> &base, GlyphIterator *glyphIterator, const LEFontInstance *fontInstance, LEErrorCode &success) const
{
    LEGlyphID glyphID       = glyphIterator->getCurrGlyphID();
    le_int32  coverageIndex = getGlyphCoverage(base, glyphID, success);
    le_uint16 eeCount       = SWAPW(entryExitCount);

    LEReferenceToArrayOf<EntryExitRecord>
        entryExitRecordsArrayRef(base, success, entryExitRecords, coverageIndex);

    if (coverageIndex < 0 || coverageIndex >= eeCount || LE_FAILURE(success)) {
        glyphIterator->setCursiveGlyph();
        return 0;
    }

    LEPoint entryAnchor, exitAnchor;
    Offset entryOffset = SWAPW(entryExitRecords[coverageIndex].entryAnchor);
    Offset exitOffset  = SWAPW(entryExitRecords[coverageIndex].exitAnchor);

    if (entryOffset != 0) {
        const AnchorTable *entryAnchorTable = (const AnchorTable *) ((char *) this + entryOffset);

        entryAnchorTable->getAnchor(glyphID, fontInstance, entryAnchor);
        glyphIterator->setCursiveEntryPoint(entryAnchor);
    } else {

    }

    if (exitOffset != 0) {
        const AnchorTable *exitAnchorTable = (const AnchorTable *) ((char *) this + exitOffset);

        exitAnchorTable->getAnchor(glyphID, fontInstance, exitAnchor);
        glyphIterator->setCursiveExitPoint(exitAnchor);
    } else {

    }

    return 1;
}
