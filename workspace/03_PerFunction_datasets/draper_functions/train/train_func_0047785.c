ScanSARRecipeFCN( CeosSARVolume_t *volume, void *token )
{
    struct CeosSARImageDesc *ImageDesc = &(volume->ImageDesc);

    memset( ImageDesc, 0, sizeof( struct CeosSARImageDesc ) );

    if( CeosDefaultRecipe( volume, token ) )
    {
	ImageDesc->Lines *= 2;
	return 1;
    }

    return 0;
}
