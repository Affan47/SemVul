CmdChangeFloorDirect(void)
{
    int tag;
    int flat;
    int sectorIndex;

    tag = LONG(*PCodePtr);
    ++PCodePtr;
    flat = R_FlatNumForName(ACStrings[LONG(*PCodePtr)]);
    ++PCodePtr;
    sectorIndex = -1;
    while ((sectorIndex = P_FindSectorFromTag(tag, sectorIndex)) >= 0)
    {
        sectors[sectorIndex].floorpic = flat;
    }
    return SCRIPT_CONTINUE;
}
