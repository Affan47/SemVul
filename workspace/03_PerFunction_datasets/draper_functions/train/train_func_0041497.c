GetFirstMatch( OGRField *psKey )

{
    GByte *pabyKey = BuildKey( psKey );
    long nFID;

    nFID = poINDFile->FindFirst( iIndex, pabyKey );
    if( nFID < 1 )
        return OGRNullFID;
    else
        return nFID - 1;
}
