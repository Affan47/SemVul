moveMRDRbetweenSQs( DcmSequenceOfItems &fromSQ,
                                             DcmSequenceOfItems &toSQ )
{
    OFCondition l_error = EC_Normal;

    unsigned long num = fromSQ.card();
    for (unsigned long i = 0, j = 0; i < num; i++)
    {
        DcmDirectoryRecord *dRec;
        dRec = OFstatic_cast(DcmDirectoryRecord *, fromSQ.getItem( j ));
        if (dRec != NULL && dRec->getRecordType() == ERT_Mrdr)
        {
            toSQ.insert( dRec );
            fromSQ.remove( j );
        } else
            j++;
    }

    return l_error;
}
