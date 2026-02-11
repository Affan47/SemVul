ResetReading()

{
    if (!TouchLayer())
        return;

    iMatchingFID = 0;

    iNextShapeId = 0;

    if( bHeaderDirty && bUpdateAccess )
        SyncToDisk();
}
