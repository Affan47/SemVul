Write()

{
    if( !GetDirty() )
        return CE_None;

    if( poBand == NULL )
        return CE_Failure;

    MarkClean();

    if (poBand->eFlushBlockErr == CE_None)
        return poBand->IWriteBlock( nXOff, nYOff, pData );
    else
        return poBand->eFlushBlockErr;
}
