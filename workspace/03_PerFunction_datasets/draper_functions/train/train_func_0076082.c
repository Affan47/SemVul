MfpdtfReadAllocateVariantHeader( Mfpdtf_t mfpdtf,
                                                               int datalen )
{
    if( mfpdtf->read.pVariantHeader )
    {
        free( mfpdtf->read.pVariantHeader );
        mfpdtf->read.pVariantHeader = 0;
    }
    mfpdtf->read.lenVariantHeader = datalen;
    if( datalen )
    {
        mfpdtf->read.pVariantHeader = malloc( datalen );
    }
    return mfpdtf->read.pVariantHeader;
}
