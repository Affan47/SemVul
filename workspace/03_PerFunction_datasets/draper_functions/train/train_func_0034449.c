SetPosition()

{


    if( nFilePos == 0 )
    {
        nFilePos = HFAAllocateSpace( psHFA,
                                     psHFA->nEntryHeaderLength
                                     + nDataSize );

        if( nDataSize > 0 )
            nDataPos = nFilePos + psHFA->nEntryHeaderLength;
    }


    for( HFAEntry *poThisChild = poChild;
         poThisChild != NULL;
         poThisChild = poThisChild->poNext )
    {
        poThisChild->SetPosition();
    }
}
