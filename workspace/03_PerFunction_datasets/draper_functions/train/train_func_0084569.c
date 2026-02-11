readHeaderNumbers()
{
    if (pGTMFile == NULL)
        return FALSE;


    if (VSIFSeekL(pGTMFile, NWPTSTYLES_OFFSET, SEEK_SET) != 0)
        return FALSE;

    nwptstyles = readInt(pGTMFile);
    if (nwptstyles < 0)
        return FALSE;


    if ( VSIFSeekL(pGTMFile, NWPTS_OFFSET, SEEK_SET) != 0)
        return FALSE;

    nwpts = readInt(pGTMFile);
    if (nwpts < 0)
        return FALSE;


    ntcks = readInt(pGTMFile);
    if (ntcks < 0)
        return FALSE;


    if ( VSIFSeekL(pGTMFile, NMAPS_OFFSET, SEEK_SET) != 0)
        return FALSE;

    n_maps = readInt(pGTMFile);
    if (n_maps < 0)
        return FALSE;


    n_tk = readInt(pGTMFile);
    if (n_tk < 0)
        return FALSE;


    headerSize = 99;
    unsigned short stringSize;


    if ( VSIFSeekL(pGTMFile, 99, SEEK_SET) != 0)
        return FALSE;
    stringSize = readUShort(pGTMFile);
    headerSize += stringSize + 2;


    if ( VSIFSeekL(pGTMFile, stringSize, SEEK_CUR) != 0)
        return FALSE;
    stringSize = readUShort(pGTMFile);
    headerSize += stringSize + 2;


    if ( VSIFSeekL(pGTMFile, stringSize, SEEK_CUR) != 0)
        return FALSE;
    stringSize = readUShort(pGTMFile);
    headerSize += stringSize + 2;


    if ( VSIFSeekL(pGTMFile, stringSize, SEEK_CUR) != 0)
        return FALSE;
    stringSize = readUShort(pGTMFile);
    headerSize += stringSize + 2;


    if ( VSIFSeekL(pGTMFile, headerSize + 34, SEEK_SET) != 0)
        return FALSE;
    if (readInt(pGTMFile) != 217)
    {
        CPLError( CE_Warning, CPLE_AppDefined,
                  "You are attempting to open a file that is not using WGS84 datum.\n"
                  "Coordinates will be returned as if they were WGS84, but no reprojection will be done.");
    }


    firstWaypointOffset = findFirstWaypointOffset();
    if (firstWaypointOffset == 0)
        return FALSE;
    actualWaypointOffset = firstWaypointOffset;

    firstTrackpointOffset = findFirstTrackpointOffset();
    if (firstTrackpointOffset == 0)
        return FALSE;
    actualTrackpointOffset = firstTrackpointOffset;


    firstTrackOffset = findFirstTrackOffset();
    if (firstTrackOffset == 0)
        return FALSE;
    actualTrackOffset = firstTrackOffset;

    return TRUE;
}
