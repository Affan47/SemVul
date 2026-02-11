IsEmpty(  ) const
{
    for( int iRing = 0; iRing < nRingCount; iRing++ )
        if (papoRings[iRing]->IsEmpty() == FALSE)
            return FALSE;
    return TRUE;
}
