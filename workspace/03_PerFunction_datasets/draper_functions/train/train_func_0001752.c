applySubtable(const LookupSubtable *lookupSubtable, le_uint16 lookupType,
                                                       GlyphIterator *glyphIterator,
                                                       const LEFontInstance *fontInstance,
                                                       LEErrorCode& success) const
{
    if (LE_FAILURE(success)) {
        return 0;
    }

    le_uint32 delta = 0;

    switch(lookupType)
    {
    case 0:
        break;

    case gpstSingle:
    {
        const SinglePositioningSubtable *subtable = (const SinglePositioningSubtable *) lookupSubtable;

        delta = subtable->process(glyphIterator, fontInstance);
        break;
    }

    case gpstPair:
    {
        const PairPositioningSubtable *subtable = (const PairPositioningSubtable *) lookupSubtable;

        delta = subtable->process(glyphIterator, fontInstance);
        break;
    }

    case gpstCursive:
    {
        const CursiveAttachmentSubtable *subtable = (const CursiveAttachmentSubtable *) lookupSubtable;

        delta = subtable->process(glyphIterator, fontInstance);
        break;
    }

    case gpstMarkToBase:
    {
        const MarkToBasePositioningSubtable *subtable = (const MarkToBasePositioningSubtable *) lookupSubtable;

        delta = subtable->process(glyphIterator, fontInstance);
        break;
    }

     case gpstMarkToLigature:
    {
        const MarkToLigaturePositioningSubtable *subtable = (const MarkToLigaturePositioningSubtable *) lookupSubtable;

        delta = subtable->process(glyphIterator, fontInstance);
        break;
    }

    case gpstMarkToMark:
    {
        const MarkToMarkPositioningSubtable *subtable = (const MarkToMarkPositioningSubtable *) lookupSubtable;

        delta = subtable->process(glyphIterator, fontInstance);
        break;
    }

   case gpstContext:
    {
        const ContextualPositioningSubtable *subtable = (const ContextualPositioningSubtable *) lookupSubtable;

        delta = subtable->process(this, glyphIterator, fontInstance, success);
        break;
    }

    case gpstChainedContext:
    {
        const ChainingContextualPositioningSubtable *subtable = (const ChainingContextualPositioningSubtable *) lookupSubtable;

        delta = subtable->process(this, glyphIterator, fontInstance, success);
        break;
    }

    case gpstExtension:
    {
        const ExtensionSubtable *subtable = (const ExtensionSubtable *) lookupSubtable;

        delta = subtable->process(this, lookupType, glyphIterator, fontInstance, success);
        break;
    }

    default:
        break;
    }

    return delta;
}
