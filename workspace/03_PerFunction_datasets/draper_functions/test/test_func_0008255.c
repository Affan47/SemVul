deleteItems( void )
{
    if ( mCache )
    {
        delete mCache ;
        mCache = NULL ;
    }

    EntryIter crntEntry, endEntry;
    crntEntry = mTagEntries.begin();
    endEntry = mTagEntries.end();

    while( crntEntry != endEntry )
    {
        delete (*crntEntry).second;
        crntEntry++ ;
    }
    mTagEntries.clear();

    SubIFDIter crntSubIFD, endSubIFD;
    crntSubIFD = mSubDirs.begin();
    endSubIFD = mSubDirs.end();
    while( crntSubIFD != endSubIFD )
    {
        ExifIFDVec dirVec = (*crntSubIFD).second ;
        for (unsigned int i=0; i<dirVec.size(); i++)
        {
            delete dirVec[i];
        }
        dirVec.clear();
        crntSubIFD++;
    }
    mSubDirs.clear();

    if (mImage)
    {
        exifDeleteImageDesc( *mImage ) ;
        delete mImage ;
        mImage = NULL ;
    }

    if (mCompressedThumb)
    {
        delete [] mCompressedThumb;
        mCompressedThumb = NULL;
    }

    return;
}
