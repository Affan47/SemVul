ensMarkerClearMarkermaplocations(EnsPMarker marker)
{
    EnsPMarkermaplocation mml = NULL;

    if (!marker)
        return ajFalse;

    while (ajListPop(marker->Markermaplocations, (void **) &mml))
        ensMarkermaplocationDel(&mml);

    return ajTrue;
}
